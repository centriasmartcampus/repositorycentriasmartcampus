#ifndef CENTRIAHTTPSCLIENT_H
#define CENTRIAHTTPSCLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QUrl>

#include "sclog.h"

class CentriaHTTPSClient : public QObject
{
    Q_OBJECT
public:
    explicit CentriaHTTPSClient(QObject *parent = nullptr);
    ~CentriaHTTPSClient();

    void Connect(QString ipAddress, quint16 port, bool acceptSelfSignedCertificates = false);

public slots:
    void Connected();
    void ReadyRead();
    void Encrypted();
    void Error(QAbstractSocket::SocketError);
    void SSLErrors(const QList<QSslError> &errors);

signals:

private:
    QSslSocket *_qSSLSocket = nullptr;
    bool _acceptSelfSignedCertificates = false;

    QByteArray CreatePOSTRequest(QByteArray content);

};

#endif // CENTRIAHTTPSCLIENT_H
