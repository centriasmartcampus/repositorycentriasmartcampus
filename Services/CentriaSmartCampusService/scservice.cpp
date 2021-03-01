#include "scservice.h"

SCService::SCService(QObject *parent) : QObject(parent)
{
    SCLog::AddDebug("SCService::SCService Constructor start");

    DTO = SCServiceDTO("SCService");
    if(DTO.TCPListener.size() > 0)
    {
        _tcpListener = new SCTCPListener(DTO.TCPListener, this);
        connect(_tcpListener, SIGNAL(NewRequest(SCFastCGIRequest&)),this, SLOT(NewRequest(SCFastCGIRequest&)));
        if(_tcpListener->DTO.TCPPort > 0)
        {
            _tcpListener->Start();
        }
    }

    SCLog::AddDebug("SCService::SCService Constructor end");
}

SCService::~SCService()
{
    if(_tcpListener != nullptr)
    {
        delete _tcpListener;
    }
}

void SCService::NewRequest(SCFastCGIRequest &scFastCGIRequest)
{
    scFastCGIRequest.Response.append("Testi\n\n\n");
    scFastCGIRequest.Response.append("Mitä ihmettä <br> toinen rivi\n");
    scFastCGIRequest.Response.append(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));


}
