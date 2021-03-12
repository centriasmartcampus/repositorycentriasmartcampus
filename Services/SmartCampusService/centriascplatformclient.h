#ifndef CENTRIASCPLATFORMCLIENT_H
#define CENTRIASCPLATFORMCLIENT_H

#include <QObject>

#include "DTO/centriascplatformclientdto.h"
#include "../Common/centriahttpsclient.h"

class CentriaSCPlatformClient : public QObject
{
    Q_OBJECT
public:
    CentriaSCPlatformClientDTO DTO;

    explicit CentriaSCPlatformClient(QString id, QObject *parent = nullptr);
    ~CentriaSCPlatformClient();

signals:

private:
    CentriaHTTPSClient* _centriaHTTPSClient = nullptr;

};

#endif // CENTRIASCPLATFORMCLIENT_H
