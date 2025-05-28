#include "servo_server.h"
#include <QCoreApplication>
#include <QDebug>

ServoServer::ServoServer(QObject *parent)
    : QTcpServer(parent)
{
    socketBt = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(socketBt, &QBluetoothSocket::connected, this, []() {
        qDebug() << "✅ Connecté au module Bluetooth.";
    });

    connect(socketBt, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            [](QBluetoothSocket::SocketError error) {
                qDebug() << " Erreur Bluetooth:" << error;
            });

    qDebug() << "Connexion à l'adresse Bluetooth : B8:27:EB:64:94:7A";

    socketBt->connectToService(QBluetoothAddress("B8:27:EB:64:94:7A"), 1); // Adresse de ton module Bluetooth
}

void ServoServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Angle reçu via TCP:" << data.trimmed();

        if (socketBt->isOpen()) {
            socketBt->write(data);
            qDebug() << "Transmis par Bluetooth.";
        } else {
            qDebug() << "Bluetooth non connecté.";
        }
    });

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QObject::deleteLater);
}
