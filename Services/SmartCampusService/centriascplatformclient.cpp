#include "centriascplatformclient.h"

CentriaSCPlatformClient::CentriaSCPlatformClient(QString id, QObject *parent) : QObject(parent)
{
    SCLog::AddDebug(QString("CentriaSCPlatformClient::CentriaSCPlatformClient(%1) start").arg(id));

    DTO = CentriaSCPlatformClientDTO(id);

    if(DTO.IPAddress.size() > 0 && DTO.Port > 0)
    {
        _centriaHTTPSClient = new CentriaHTTPSClient(this);
        _centriaHTTPSClient->Connect(DTO.IPAddress, DTO.Port, DTO.AcceptSelfSignedCertificates);
    }

    SCLog::AddDebug(QString("CentriaSCPlatformClient::CentriaSCPlatformClient(%1) end").arg(id));
}

CentriaSCPlatformClient::~CentriaSCPlatformClient()
{
    if(_centriaHTTPSClient != nullptr)
    {
        delete _centriaHTTPSClient;
    }
}
