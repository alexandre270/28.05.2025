#ifndef SERVO_SERVER_H
#define SERVO_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QBluetoothSocket>
#include <QBluetoothServiceInfo>
#include <QBluetoothAddress>

class ServoServer : public QTcpServer {
    Q_OBJECT

public:
    explicit ServoServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QBluetoothSocket *socketBt;
};

#endif // SERVO_SERVER_H
