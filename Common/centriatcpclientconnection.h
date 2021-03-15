#ifndef CENTRIATCPCLIENTCONNECTION_H
#define CENTRIATCPCLIENTCONNECTION_H

#include <QObject>
#include <QTcpSocket>

#include "sclog.h"

class CentriaTCPClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit CentriaTCPClientConnection(QTcpSocket* newSocket, QObject *parent = nullptr);
    ~CentriaTCPClientConnection();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

signals:
    void Disconnected(qintptr socketDescriptor);
    void ReadyRead(qintptr socketDescriptor, QByteArray& data);

private:
    QTcpSocket* _qTCPSocket;
    qintptr _socketDescriptor = -1;


};

#endif // CENTRIATCPCLIENTCONNECTION_H
