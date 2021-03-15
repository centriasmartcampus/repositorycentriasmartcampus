#ifndef CENTRIASCSERVICE_H
#define CENTRIASCSERVICE_H

#include <QObject>

#include "sclog.h"
#include "DTO/centriascservicedto.h"
#include "../Common/centriafastcgitcplistener.h"
#include "centriascplatformclient.h"
#include "../Common/centriatcpserver.h"

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


signals:

private:
    CentriaFastCGITCPListener *_centriaFastCGITCPListener = nullptr;
    CentriaSCPlatformClient *_centriaSCPlatformClient = nullptr;
    CentriaTCPServer *_centriaTCPServer = nullptr;

};

#endif // CENTRIASCSERVICE_H
