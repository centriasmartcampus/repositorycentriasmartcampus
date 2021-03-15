#include "centriatcpclientconnection.h"


CentriaTCPClientConnection::CentriaTCPClientConnection(QTcpSocket *newSocket, QObject *parent)
{
    SCLog::AddLog(QString("CentriaTCPClientConnection::CentriaTCPClientConnection(%1) start").arg(newSocket->socketDescriptor()));
    _qTCPSocket = newSocket;
    _socketDescriptor = _qTCPSocket->socketDescriptor();
    connect(_qTCPSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_qTCPSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_qTCPSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(_qTCPSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    SCLog::AddLog(QString("CentriaTCPClientConnection::CentriaTCPClientConnection(%1) end").arg(newSocket->socketDescriptor()));
}

CentriaTCPClientConnection::~CentriaTCPClientConnection()
{
    SCLog::AddLog(QString("CentriaTCPClientConnection::~CentriaTCPClientConnection(%1) start").arg(_socketDescriptor));
    _qTCPSocket->close();
    _qTCPSocket->deleteLater();
    SCLog::AddLog(QString("CentriaTCPClientConnection::~CentriaTCPClientConnection(%1) start").arg(_socketDescriptor));
}

void CentriaTCPClientConnection::connected()
{
    SCLog::AddDebug(QString("CentriaTCPClientConnection::connected(%1) start").arg(_socketDescriptor));

    SCLog::AddDebug(QString("CentriaTCPClientConnection::connected(%1) end").arg(_socketDescriptor));
}

void CentriaTCPClientConnection::disconnected()
{
    SCLog::AddDebug(QString("CentriaTCPClientConnection::disconnected(%1) start").arg(_socketDescriptor));
    emit Disconnected(_socketDescriptor);
    SCLog::AddDebug(QString("CentriaTCPClientConnection::disconnected(%1) end").arg(_socketDescriptor));
}

void CentriaTCPClientConnection::bytesWritten(qint64 bytes)
{
    SCLog::AddDebug(QString("CentriaTCPClientConnection::bytesWritten(%1) start").arg(_socketDescriptor));

    SCLog::AddDebug(QString("CentriaTCPClientConnection::bytesWritten(%1) end").arg(_socketDescriptor));
}

void CentriaTCPClientConnection::readyRead()
{
    SCLog::AddDebug(QString("CentriaTCPClientConnection::readyRead(%1) start").arg(_socketDescriptor));
    QByteArray data = _qTCPSocket->readAll();
    emit ReadyRead(_socketDescriptor, data);
    SCLog::AddDebug(QString("CentriaTCPClientConnection::readyRead(%1) end").arg(_socketDescriptor));
}

