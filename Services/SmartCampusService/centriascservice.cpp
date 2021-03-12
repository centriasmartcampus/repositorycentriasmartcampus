#include "centriascservice.h"

CentriaSCService::CentriaSCService(QObject *parent) : QObject(parent)
{
    SCLog::AddDebug("CentriaSCService::CentriaSCService Constructor start");

    DTO = CentriaSCServiceDTO(SERVICE_NAME);
    if(DTO.FastCGIListener.size() > 0)
    {

        _centriaFastCGITCPListener = new CentriaFastCGITCPListener(DTO.FastCGIListener, this);
        connect(_centriaFastCGITCPListener, SIGNAL(NewRequest(CentriaFastCGIRequest&)),this, SLOT(NewRequest(CentriaFastCGIRequest&)));
    }

    if(DTO.PlatformClient.size() > 0)
    {
        _centriaSCPlatformClient = new CentriaSCPlatformClient(DTO.PlatformClient, this);
    }

    SCLog::AddDebug("CentriaSCService::CentriaSCService Constructor end");
}

CentriaSCService::~CentriaSCService()
{
    SCLog::AddDebug("CentriaSCService::~CentriaSCService Constructor start");
    if(_centriaFastCGITCPListener != nullptr)
    {
        delete _centriaFastCGITCPListener;
    }
    SCLog::AddDebug("CentriaSCService::~CentriaSCService Constructor end");
}

void CentriaSCService::NewRequest(CentriaFastCGIRequest &centriaFastCGIRequest)
{
    centriaFastCGIRequest.Response.append("Testi\n\n\n");
    centriaFastCGIRequest.Response.append("Mitä ihmettä <br> toinen rivi\n");
    centriaFastCGIRequest.Response.append(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
}
