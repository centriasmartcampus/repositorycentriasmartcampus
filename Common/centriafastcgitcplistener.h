#ifndef CENTRIAFASTCGITCPLISTENER_H
#define CENTRIAFASTCGITCPLISTENER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QQueue>
#include <QReadWriteLock>

#include "sclog.h"
#include "centriafastcgirequest.h"
#include "DTO/centriafastcgitcplistenerdto.h"

typedef struct {
    unsigned char version;
    unsigned char type;
    unsigned char requestIdB1;
    unsigned char requestIdB0;
    unsigned char contentLengthB1;
    unsigned char contentLengthB0;
    unsigned char paddingLength;
    unsigned char reserved;
} FastCGI_Header;

typedef struct {
    unsigned char roleB1;
    unsigned char roleB0;
    unsigned char flags;
    unsigned char reserved[5];
} FastCGI_BeginRequestBody;

#define FastCGI_HEADER_LEN 8

#define FastCGI_VERSION_1  1

#define FastCGI_BEGIN_REQUEST     1
//#define FastCGI_ABORT_REQUEST     2
//#define FastCGI_END_REQUEST       3
#define FastCGI_PARAMS            4
#define FastCGI_STDIN             5
#define FastCGI_STDOUT            6
//#define FastCGI_STDERR            7
//#define FastCGI_DATA              8
//#define FastCGI_GET_VALUES        9
//#define FastCGI_GET_VALUES_RESULT 10
//#define FastCGI_UNKNOWN_TYPE      11
//#define FastCGI_MAXTYPE (FCGI_UNKNOWN_TYPE)


class CentriaFastCGITCPListener : public QObject
{
    Q_OBJECT
public:
    CentriaFastCGITCPListenerDTO DTO;

    explicit CentriaFastCGITCPListener(QString tcpListenerName, QObject *parent = nullptr);
    ~CentriaFastCGITCPListener();

signals:
    void NewRequest(CentriaFastCGIRequest& scFastCGIRequest);

public slots:
    void readyRead();
    void newConnection();
    void connected();
    void disconnected();
    void destroyed(QObject * = nullptr);

    void RequestParser(CentriaFastCGIRequest& centriaFastCGIRequest);
    QByteArray CreateSendData(CentriaFastCGIRequest& centriaFastCGIRequest);

protected:

private:
    QTcpServer *_qTCPServer = nullptr;
    QTcpSocket *_qTCPSocket = nullptr;
};



#endif // CENTRIAFASTCGITCPLISTENER_H
