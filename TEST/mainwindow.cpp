#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "server.h"
#include "camera.h"
#include "dbmanager.h"
#include "videostream.h"

#include <QDebug>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QHostAddress>
#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientSocket(nullptr)
{
    qDebug() << "💡 Début MainWindow";

    ui->setupUi(this);
    qDebug() << "✅ UI chargé";

    // Label de commande
    commandLabel = new QLabel(this);
    commandLabel->setObjectName("commandLabel");
    ui->verticalLayout->addWidget(commandLabel);

    // Objets principaux
    client = new Client(this);
    server = new Server(client, this);
    dbManager = new DBManager(this);
    camera = new Camera(this);
    qDebug() << "✅ Objets instanciés";

    connect(client, &Client::sensorDataReceived, server, &Server::archiveSensorData);
    qDebug() << "✅ Signal capteur connecté";

    // Flux vidéo sécurisé
    try {
        videoStream = new VideoStream("udp://192.168.0.21:1234", this);

        connect(videoStream, &VideoStream::frameReady, this, [=](const QImage &img) {
            if (!img.isNull()) {
                updateFrame(img);
                client->handleVideoFrame(img);
            } else {
                qDebug() << "⚠️ Image vidéo invalide ignorée.";
            }
        });

        videoStream->start();
        qDebug() << "✅ Flux vidéo actif";
    } catch (...) {
        qDebug() << "❌ Erreur lors du démarrage du flux vidéo.";
    }

    // Configuration du slider servo
    ui->servoSlider->setRange(0, 180);
    ui->servoSlider->setValue(90);
    ui->servoAngleLabel->setText("Angle: 90°");

    connect(ui->servoSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->servoAngleLabel->setText("Angle: " + QString::number(value) + "°");
    });

    connect(ui->sendServoButton, &QPushButton::clicked, this, [=]() {
        int angle = ui->servoSlider->value();
        QString message = QString::number(angle) + "\n";

        // === Envoi TCP ===
        QTcpSocket *servoSocket = new QTcpSocket(this);
        servoSocket->connectToHost(QHostAddress("192.168.1.42"), 12345);

        if (servoSocket->waitForConnected(2000)) {
            servoSocket->write(message.toUtf8());
            servoSocket->waitForBytesWritten();
            servoSocket->close();
            commandLabel->setText("Angle envoyé : " + QString::number(angle));
            qDebug() << "✅ Angle envoyé au servomoteur TCP :" << angle;
        } else {
            commandLabel->setText("Erreur : Servo non joignable !");
            qDebug() << "❌ Connexion échouée vers servo.";
        }

        servoSocket->deleteLater();

        // === Envoi Bluetooth RFCOMM ===
        QFile rfcomm("/dev/rfcomm0");
        if (rfcomm.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
            QTextStream out(&rfcomm);
            out << "angle:" << angle << "\n";
            rfcomm.close();
            qDebug() << "✅ Angle envoyé via Bluetooth :" << angle;
        } else {
            qDebug() << "❌ Impossible d’ouvrir /dev/rfcomm0 pour envoi Bluetooth.";
            QMessageBox::warning(this, "Bluetooth", "Échec de l’envoi Bluetooth : /dev/rfcomm0 inaccessible.");
        }
    });

    qDebug() << "✅ Initialisation complète MainWindow";
}

MainWindow::~MainWindow()
{
    delete videoStream;
    delete camera;
    delete server;
    delete client;
    delete dbManager;
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();
    client->sendMovementCommand(message);
    ui->messagesTextEdit->append("Commande envoyée: " + message);
    commandLabel->setText("Commande: " + message);
}

void MainWindow::on_moveButton_clicked()
{
    QString command = ui->commandLineEdit->text();
    client->sendMovementCommand(command);
    ui->commandsTextEdit->append("Commande de mouvement envoyée: " + command);
    commandLabel->setText("Commande: " + command);
}

void MainWindow::on_fetchDataButton_clicked()
{
    QStringList data = dbManager->fetchData();
    ui->measurementsTextEdit->clear();
    for (const QString &item : data) {
        ui->measurementsTextEdit->append(item);
    }
}

void MainWindow::on_captureScreenButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString filename = QString("capture_%1.png").arg(timestamp);

    if (screenshot.save(filename)) {
        dbManager->insertSensorData("Capture d'écran", filename);
        ui->commandsTextEdit->append("Capture d'écran sauvegardée: " + filename);
    } else {
        qDebug() << "Erreur lors de la sauvegarde de la capture d'écran.";
    }
}

void MainWindow::updateFrame(const QImage &image)
{
    ui->videoLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::updateMeasurements(const QString &measurements)
{
    ui->measurementsTextEdit->setPlainText(measurements);
}
