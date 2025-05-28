#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class Client;
class Server;
class Camera;
class DBManager;
class VideoStream;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_moveButton_clicked();
    void on_fetchDataButton_clicked();
    void on_captureScreenButton_clicked();
    void updateFrame(const QImage &image);
    void updateMeasurements(const QString &measurements);


private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;

    Client *client;
    Server *server;
    Camera *camera;
    DBManager *dbManager;
    VideoStream *videoStream;

    QLabel *commandLabel;
};

#endif // MAINWINDOW_H
