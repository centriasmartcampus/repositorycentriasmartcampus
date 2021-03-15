#ifndef CENTRIATCPCLIENT_H
#define CENTRIATCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "DTO/centriatcpclientdto.h"

class CentriaTCPClient : public QObject
{
    Q_OBJECT
public:
    CentriaTCPClientDTO DTO;

    explicit CentriaTCPClient(QString tcpClientName, QObject *parent = nullptr);
    ~CentriaTCPClient();

    QAbstractSocket::SocketState SocketState();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

signals:
    void Disconnected(qintptr socketDescriptor);

private:
    QTcpSocket *_qTcpSocket = nullptr;


};

#endif // CENTRIATCPCLIENT_H
