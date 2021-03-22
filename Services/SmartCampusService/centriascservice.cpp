#include "centriascservice.h"

CentriaSCService::CentriaSCService(QObject *parent) : QObject(parent)
{
    SCLog::AddDebug("CentriaSCService::CentriaSCService start");

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

    if(DTO.CentriaTCPServer.size() > 0)
    {
        _centriaTCPServer = new CentriaTCPServer(DTO.CentriaTCPServer);
    }



    //_timerId = startTimer(100);

    SCLog::AddDebug("CentriaSCService::CentriaSCService end");
}

CentriaSCService::~CentriaSCService()
{
    SCLog::AddDebug("CentriaSCService::~CentriaSCService start");
    if(_timerId >= 0)
    {
        killTimer(_timerId);
    }

    if(_centriaFastCGITCPListener != nullptr)
    {
        delete _centriaFastCGITCPListener;
    }

    if(_centriaSCPlatformClient != nullptr)
    {
        delete _centriaSCPlatformClient;
    }

    if(_centriaTCPServer != nullptr)
    {
        delete _centriaTCPServer;
    }

    if(_centriaTCPClient != nullptr)
    {
        delete _centriaTCPClient;
    }

    SCLog::AddDebug("CentriaSCService::~CentriaSCService end");
}

void CentriaSCService::NewRequest(CentriaFastCGIRequest &centriaFastCGIRequest)
{
    //centriaFastCGIRequest.Response.append("Testi\n\n\n");
    //centriaFastCGIRequest.Response.append("Mitä ihmettä <br> toinen rivi\n");
    centriaFastCGIRequest.Response.append("Hello Vadym!");
    centriaFastCGIRequest.Response.append(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
}

void CentriaSCService::Disconnected(qintptr socketDescriptor)
{
    SCLog::AddLog(QString("CentriaSCService::Disconnected (SocketDescriptor:%1) start").arg(socketDescriptor));



    SCLog::AddLog(QString("CentriaSCService::Disconnected (SocketDescriptor:%1) end").arg(socketDescriptor));
}

void CentriaSCService::timerEvent(QTimerEvent *)
{
    if(_centriaTCPClient == nullptr && DTO.CentriaTCPClient.size() > 0)
    {
        _centriaTCPClient = new CentriaTCPClient(DTO.CentriaTCPClient);
        connect(_centriaTCPClient, SIGNAL(Disconnected(qintptr)), this, SLOT(Disconnected(qintptr)));
    }
    else
    {
        QAbstractSocket::SocketState socketState = _centriaTCPClient->SocketState();
        if(socketState != QAbstractSocket::SocketState::ConnectedState)
        {
            SCLog::AddLog(QString("CentriaTCPClient(%1) has lost connection").arg(DTO.ID));
            delete _centriaTCPClient;
            _centriaTCPClient = nullptr;
        }
    }

}

