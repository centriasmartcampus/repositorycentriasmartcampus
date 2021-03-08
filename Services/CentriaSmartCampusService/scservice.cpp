#include "scservice.h"

SCService::SCService(QObject *parent) : QObject(parent)
{
    SCLog::AddDebug("SCService::SCService Constructor start");

    DTO = SCServiceDTO("SCService");
    if(DTO.TCPListener.size() > 0)
    {
        _scTCPListener = new SCTCPListener(DTO.TCPListener, this);
        connect(_scTCPListener, SIGNAL(NewRequest(SCFastCGIRequest&)),this, SLOT(NewRequest(SCFastCGIRequest&)));
        if(_scTCPListener->DTO.TCPPort > 0)
        {
            _scTCPListener->Start();
        }
    }

    SCLog::AddDebug("SCService::SCService Constructor end");
}

SCService::~SCService()
{
    if(_scTCPListener != nullptr)
    {
        delete _scTCPListener;
    }
}

void SCService::NewRequest(SCFastCGIRequest &scFastCGIRequest)
{

    //scFastCGIRequest.Response.append("Testi\n\n\n");
    //scFastCGIRequest.Response.append("Mitä ihmettä <br> toinen rivi\n");
    //scFastCGIRequest.Response.append(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));

    scFastCGIRequest.Response.append("{\n");
    foreach(QString key, scFastCGIRequest.Parameters.keys())
    {
        scFastCGIRequest.Response.append(QString("\"%1\": \"%2\",\n").arg(key).arg(scFastCGIRequest.Parameters[key]));
    }
    scFastCGIRequest.Response.append(QString("\"Request\": "));
    scFastCGIRequest.Response.append(QString("\"%1\"\n").arg(QString(scFastCGIRequest.Request)));
    scFastCGIRequest.Response.append(QString("\"Content\": \"%1\"\n").arg(QString(scFastCGIRequest.Content)));
    scFastCGIRequest.Response.append("}\n");


}
