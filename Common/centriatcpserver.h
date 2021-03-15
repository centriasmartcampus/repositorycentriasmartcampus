#ifndef CENTRIATCPSERVER_H
#define CENTRIATCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "sclog.h"
#include "DTO/centriatcpserverdto.h"
#include "centriatcpclientconnection.h"

class CentriaTCPServer : public QObject
{
    Q_OBJECT
public:
    CentriaTCPServerDTO DTO;
    explicit CentriaTCPServer(QString tcpServerName, QObject *parent = nullptr);
    ~CentriaTCPServer();

public slots:
    void newConnection();
    void Disconnected(qintptr socketDescriptor);
    void ReadyRead(qintptr socketDescriptor, QByteArray& data);

protected:
    void timerEvent(QTimerEvent *);

signals:

private:
    int _timerId = -1;
    QTcpServer *_qTcpServer = nullptr;
    QMap<qintptr, CentriaTCPClientConnection*> _centriaTCPClientConnections;
    QList<CentriaTCPClientConnection*> _disconnectedCentriaTCPClientConnections;

};

#endif // CENTRIATCPSERVER_H
