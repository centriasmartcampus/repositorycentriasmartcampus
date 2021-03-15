#include "centriatcpserver.h"

CentriaTCPServer::CentriaTCPServer(QString tcpServerName, QObject *parent) : QObject(parent)
{
    SCLog::AddDebug(QString("CentriaTCPServer::CentriaTCPServer(%1) start").arg(tcpServerName));
    DTO = CentriaTCPServerDTO(tcpServerName);

    if(DTO.TCPPort > 0)
    {
        _qTcpServer = new QTcpServer(this);
        connect(_qTcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
        if(!_qTcpServer->listen(QHostAddress::Any, DTO.TCPPort))
        {
            SCLog::AddError(QString("CentriaFastCGITCPListener(%1) QTcpServer could not start").arg(DTO.ID));
        }
        else
        {
            SCLog::AddLog(QString("CentriaFastCGITCPListener(%1) started").arg(DTO.ID));
            _timerId = startTimer(100);
        }
    }

    SCLog::AddDebug(QString("CentriaTCPServer::CentriaTCPServer(%1) end").arg(tcpServerName));
}

CentriaTCPServer::~CentriaTCPServer()
{
    SCLog::AddDebug(QString("CentriaTCPServer::~CentriaTCPServer start"));

    if(_timerId >= 0)
    {
        killTimer(_timerId);
    }


    foreach(CentriaTCPClientConnection *disconnectedCentriaTCPClientConnection, _disconnectedCentriaTCPClientConnections)
    {
        delete disconnectedCentriaTCPClientConnection;
    }

    foreach(CentriaTCPClientConnection *centriaTCPClientConnection, _centriaTCPClientConnections)
    {
        delete centriaTCPClientConnection;
    }

    if(_qTcpServer != nullptr)
    {
        _qTcpServer->close();
        _qTcpServer->deleteLater();
    }
    SCLog::AddDebug(QString("CentriaTCPServer::~CentriaTCPServer start"));
}

void CentriaTCPServer::newConnection()
{
    SCLog::AddLog(QString("CentriaTCPServer::newConnection(%1) start").arg(DTO.ID));
    QTcpSocket *qTcpSocket = _qTcpServer->nextPendingConnection();

    if(_centriaTCPClientConnections[qTcpSocket->socketDescriptor()] == nullptr)
    {
        CentriaTCPClientConnection *centriaTCPClientConnection = new CentriaTCPClientConnection(qTcpSocket, this);
        connect(centriaTCPClientConnection, SIGNAL(Disconnected(qintptr)), this, SLOT(Disconnected(qintptr)));
        connect(centriaTCPClientConnection, SIGNAL(ReadyRead(qintptr,QByteArray&)), this, SLOT(ReadyRead(qintptr,QByteArray&)));
        _centriaTCPClientConnections.insert(qTcpSocket->socketDescriptor(), centriaTCPClientConnection);
    }
    else
    {
        SCLog::AddError(QString("There is QTCPSocket with same SocketDescriptor(%1) exists").arg(qTcpSocket->socketDescriptor()));
    }



    SCLog::AddLog(QString("CentriaTCPServer::newConnection(%1) end").arg(DTO.ID));
}

void CentriaTCPServer::Disconnected(qintptr socketDescriptor)
{
    SCLog::AddDebug(QString("CentriaTCPServer::Disconnected(%1) start").arg(DTO.ID));
    CentriaTCPClientConnection *centriaTCPClientConnection = _centriaTCPClientConnections[socketDescriptor];
    if(centriaTCPClientConnection != nullptr)
    {
        _centriaTCPClientConnections.remove(socketDescriptor);
        _disconnectedCentriaTCPClientConnections.append(centriaTCPClientConnection);
    }
    SCLog::AddDebug(QString("CentriaTCPServer::Disconnected(%1) end").arg(DTO.ID));
}

void CentriaTCPServer::ReadyRead(qintptr socketDescriptor, QByteArray &data)
{
    SCLog::AddDebug(QString("CentriaTCPServer::ReadyRead(%1) start").arg(DTO.ID));

    SCLog::AddDebug(QString("%1: %2").arg(socketDescriptor).arg(QString(data)));

    SCLog::AddDebug(QString("CentriaTCPServer::ReadyRead(%1) end").arg(DTO.ID));
}

void CentriaTCPServer::timerEvent(QTimerEvent *)
{
    foreach(CentriaTCPClientConnection *disconnectedCentriaTCPClientConnection, _disconnectedCentriaTCPClientConnections)
    {
        delete disconnectedCentriaTCPClientConnection;
    }
    _disconnectedCentriaTCPClientConnections.clear();
}
