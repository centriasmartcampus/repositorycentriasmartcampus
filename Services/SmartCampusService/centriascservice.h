#ifndef CENTRIASCSERVICE_H
#define CENTRIASCSERVICE_H

#include <QObject>

#include "sclog.h"
#include "DTO/centriascservicedto.h"
#include "../Common/centriafastcgitcplistener.h"
#include "centriascplatformclient.h"
#include "../Common/centriatcpserver.h"
#include "../Common/centriatcpclient.h"

#define SERVICE_NAME "CentriaSCService"


class CentriaSCService : public QObject
{
    Q_OBJECT
public:
    CentriaSCServiceDTO DTO;
    explicit CentriaSCService(QObject *parent = nullptr);
    ~CentriaSCService();

public slots:
    void NewRequest(CentriaFastCGIRequest& centriaFastCGIRequest);
    void Disconnected(qintptr socketDescriptor);

protected:
    void timerEvent(QTimerEvent *);


signals:

private:
    int _timerId = -1;
    CentriaFastCGITCPListener *_centriaFastCGITCPListener = nullptr;
    CentriaSCPlatformClient *_centriaSCPlatformClient = nullptr;
    CentriaTCPServer *_centriaTCPServer = nullptr;
    CentriaTCPClient *_centriaTCPClient = nullptr;

};

#endif // CENTRIASCSERVICE_H
