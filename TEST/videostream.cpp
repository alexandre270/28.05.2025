#include "videostream.h"

VideoStream::VideoStream(const QString &url, QObject *parent)
    : QThread(parent), url(url)
{}

void VideoStream::run()
{
    AVFormatContext *formatContext = avformat_alloc_context();
    if (!formatContext) {
        qDebug() << "Erreur d'allocation AVFormatContext";
        return;
    }

    if (avformat_open_input(&formatContext, url.toStdString().c_str(), nullptr, nullptr) < 0) {
        qDebug() << "Erreur d'ouverture du flux vidéo";
        avformat_free_context(formatContext);
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qDebug() << "Impossible de lire les infos du flux";
        avformat_close_input(&formatContext);
        return;
    }

    int videoStreamIndex = -1;
    const AVCodec *codec = nullptr;
    for (unsigned int i = 0; i < formatContext->nb_streams; ++i) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            codec = avcodec_find_decoder(formatContext->streams[i]->codecpar->codec_id);
            break;
        }
    }

    if (videoStreamIndex == -1 || !codec) {
        qDebug() << "Aucun flux vidéo ou codec non trouvé";
        avformat_close_input(&formatContext);
        return;
    }

    AVCodecContext *codecContext = avcodec_alloc_context3(codec);
    if (!codecContext || avcodec_parameters_to_context(codecContext, formatContext->streams[videoStreamIndex]->codecpar) < 0 ||
        avcodec_open2(codecContext, codec, nullptr) < 0) {
        qDebug() << "Erreur d'initialisation du codec";
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return;
    }

    AVFrame *frame = av_frame_alloc();
    AVFrame *rgbFrame = av_frame_alloc();
    if (!frame || !rgbFrame) {
        qDebug() << "Erreur allocation frame";
        av_frame_free(&frame);
        av_frame_free(&rgbFrame);
        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
        return;
    }

    AVPacket packet;
    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == videoStreamIndex) {
            if (avcodec_send_packet(codecContext, &packet) == 0 &&
                avcodec_receive_frame(codecContext, frame) == 0) {

                if (!frame->data[0] || frame->width <= 0 || frame->height <= 0) {
                    qDebug() << "Frame invalide";
                    av_packet_unref(&packet);
                    continue;
                }

                SwsContext *swsCtx = sws_getContext(
                    frame->width, frame->height, codecContext->pix_fmt,
                    frame->width, frame->height, AV_PIX_FMT_RGB24,
                    SWS_BILINEAR, nullptr, nullptr, nullptr);

                if (!swsCtx) {
                    qDebug() << "Erreur création SwsContext";
                    av_packet_unref(&packet);
                    continue;
                }

                int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, frame->width, frame->height, 1);
                uint8_t *buffer = (uint8_t *)av_malloc(numBytes);
                if (!buffer) {
                    qDebug() << "Erreur allocation buffer RGB";
                    sws_freeContext(swsCtx);
                    av_packet_unref(&packet);
                    continue;
                }

                av_image_fill_arrays(rgbFrame->data, rgbFrame->linesize, buffer,
                                     AV_PIX_FMT_RGB24, frame->width, frame->height, 1);

                sws_scale(swsCtx, frame->data, frame->linesize, 0, frame->height,
                          rgbFrame->data, rgbFrame->linesize);

                QImage image(rgbFrame->data[0], frame->width, frame->height, QImage::Format_RGB888);
                emit frameReady(image.copy());

                av_free(buffer);
                sws_freeContext(swsCtx);
            }
        }
        av_packet_unref(&packet);
    }

    av_frame_free(&frame);
    av_frame_free(&rgbFrame);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
}
