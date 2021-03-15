#include "centriatcpclient.h"


CentriaTCPClient::CentriaTCPClient(QString tcpClientName, QObject *parent)
{
    SCLog::AddDebug(QString("CentriaTCPClient::CentriaTCPClient(%1) start").arg(tcpClientName));
    DTO = CentriaTCPClientDTO(tcpClientName);

    if(DTO.IPAddress.size() > 0 && DTO.Port >= 0)
    {
        _qTcpSocket = new QTcpSocket(this);
        connect(_qTcpSocket, SIGNAL(connected()), this,SLOT(connected()));
        connect(_qTcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(_qTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
        connect(_qTcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

        _qTcpSocket->connectToHost(DTO.IPAddress, DTO.Port);
    }

    SCLog::AddDebug(QString("CentriaTCPClient::CentriaTCPClient(%1) end").arg(tcpClientName));
}

CentriaTCPClient::~CentriaTCPClient()
{
    if(_qTcpSocket != nullptr)
    {
        _qTcpSocket->close();
        _qTcpSocket->deleteLater();
    }
}

QAbstractSocket::SocketState CentriaTCPClient::SocketState()
{
    QAbstractSocket::SocketState socketState = QAbstractSocket::SocketState::UnconnectedState;
    if(_qTcpSocket != nullptr)
    {
        socketState = _qTcpSocket->state();
    }
    return socketState;
}

void CentriaTCPClient::connected()
{
    SCLog::AddDebug(QString("CentriaTCPClient::connected(%1) start").arg(_qTcpSocket->socketDescriptor()));

    SCLog::AddDebug(QString("CentriaTCPClient::connected(%1) end").arg(_qTcpSocket->socketDescriptor()));
}

void CentriaTCPClient::disconnected()
{
    SCLog::AddDebug(QString("CentriaTCPClient::disconnected(%1) start").arg(_qTcpSocket->socketDescriptor()));
    emit Disconnected(_qTcpSocket->socketDescriptor());
    SCLog::AddDebug(QString("CentriaTCPClient::disconnected(%1) end").arg(_qTcpSocket->socketDescriptor()));
}

void CentriaTCPClient::bytesWritten(qint64 bytes)
{
    SCLog::AddDebug(QString("CentriaTCPClient::bytesWritten(%1) start").arg(_qTcpSocket->socketDescriptor()));

    SCLog::AddDebug(QString("CentriaTCPClient::bytesWritten(%1) end").arg(_qTcpSocket->socketDescriptor()));
}

void CentriaTCPClient::readyRead()
{
    SCLog::AddDebug(QString("CentriaTCPClient::readyRead(%1) start").arg(_qTcpSocket->socketDescriptor()));

    SCLog::AddDebug(QString("CentriaTCPClient::readyRead(%1) end").arg(_qTcpSocket->socketDescriptor()));
}
