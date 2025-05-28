#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QImage>
#include <QTcpServer>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

    void sendMovementCommand(const QString &command);
    void sendDataToAndroid(const QString &data);
    void handleVideoFrame(const QImage &image);

signals:
    void sensorDataReceived(const QString &sensorType, float value);

private slots:
    void readClientData();

private:
    QTcpSocket *robotSocket;
    QTcpSocket *flutterSocket;
    QTcpServer *flutterServer;
    bool socketWasConnected = true;

    char mapCommande(const QString &msg);
};

#endif // CLIENT_H
