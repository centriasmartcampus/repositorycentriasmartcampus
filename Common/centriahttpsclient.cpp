#include "centriahttpsclient.h"

CentriaHTTPSClient::CentriaHTTPSClient(QObject *parent) : QObject(parent)
{
    SCLog::AddDebug(QString("CentriaHTTPSClient::CentriaHTTPSClient start"));
    _qSSLSocket = new QSslSocket(this);

    connect(_qSSLSocket,SIGNAL(connected()), this, SLOT(Connected()));
    connect(_qSSLSocket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(_qSSLSocket, SIGNAL(encrypted()), this, SLOT(Encrypted()));
    connect(_qSSLSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));
    connect(_qSSLSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(SSLErrors(QList<QSslError>)));

    SCLog::AddDebug(QString("CentriaHTTPSClient::CentriaHTTPSClient end"));
}

CentriaHTTPSClient::~CentriaHTTPSClient()
{
    SCLog::AddDebug(QString("CentriaHTTPSClient::~CentriaHTTPSClient start"));
    if(_qSSLSocket != nullptr)
    {
        _qSSLSocket->close();
        _qSSLSocket->deleteLater();
    }
    SCLog::AddDebug(QString("CentriaHTTPSClient::~CentriaHTTPSClient end"));
}

void CentriaHTTPSClient::Connect(QString ipAddress, quint16 port, bool acceptSelfSignedCertificates)
{
    if(_qSSLSocket != nullptr)
    {
        _acceptSelfSignedCertificates = acceptSelfSignedCertificates;
        _qSSLSocket->connectToHostEncrypted(ipAddress, port);
    }
}

void CentriaHTTPSClient::Connected()
{
    SCLog::AddDebug(QString("CentriaHTTPSClient::Connected start"));

    QByteArray content;
    content.append("{\n");
    content.append("    \"Message\": \"Connect\",\n");
    content.append("    \"UUID\": \"24a4547ba9c3415c9cb8a990f5973112\"\n");
    content.append("}\n");
    QByteArray request = CreatePOSTRequest(content);
   _qSSLSocket->write(request);

    SCLog::AddDebug(QString("CentriaHTTPSClient::Connected end"));
}

void CentriaHTTPSClient::ReadyRead()
{
    SCLog::AddDebug(QString("CentriaHTTPSClient::ReadyRead start"));

    QByteArray content = _qSSLSocket->readAll();
    SCLog::AddDebug(content);

    SCLog::AddDebug(QString("CentriaHTTPSClient::ReadyRead end"));
}

void CentriaHTTPSClient::Encrypted()
{
    SCLog::AddDebug(QString("CentriaHTTPSClient::Encrypted start"));
    SCLog::AddDebug(QString("CentriaHTTPSClient::Encrypted end"));
}

void CentriaHTTPSClient::Error(QAbstractSocket::SocketError)
{
    SCLog::AddError(QString("CentriaHTTPSClient::Error start"));

    if(_qSSLSocket != nullptr)
    {
        SCLog::AddError(QString("%1").arg(_qSSLSocket->errorString()));
    }

    SCLog::AddError(QString("CentriaHTTPSClient::Error end"));
}

void CentriaHTTPSClient::SSLErrors(const QList<QSslError> &errors)
{
    SCLog::AddError(QString("CentriaHTTPSClient::SSLErrors start"));

    foreach(QSslError sslError, errors)
    {
        QSslError qSSLError = sslError.error();
        SCLog::AddError(QString("Error:%1 : %2").arg(qSSLError.error()).arg(sslError.errorString()));

        if(qSSLError == QSslError::SelfSignedCertificate && _acceptSelfSignedCertificates)
        {
            _qSSLSocket->ignoreSslErrors();
        }
    }

    SCLog::AddError(QString("CentriaHTTPSClient::SSLErrors end"));
}

QByteArray CentriaHTTPSClient::CreatePOSTRequest(QByteArray content)
{
    QUrl qUrl(content);
    QByteArray request;
    request.append("POST / HTTP/1.0\r\n");
    request.append("Content-Type: text/plain\r\n");
    request.append(QString("Content-Length: %1\r\n\r\n").arg(content.size()));
    request.append(content);
    request.append("\r\n\r\n");


    return request;
}
