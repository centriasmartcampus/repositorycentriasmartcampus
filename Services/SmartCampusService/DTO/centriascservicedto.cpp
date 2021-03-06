#include "centriascservicedto.h"

CentriaSCServiceDTO::CentriaSCServiceDTO()
{

}

CentriaSCServiceDTO::CentriaSCServiceDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaSCServiceDTO::CentriaSCServiceDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaSCServiceDTO::CentriaSCServiceDTO(%1) end").arg(id));
}

void CentriaSCServiceDTO::LoadConfiguration()
{
    SCLog::AddDebug("CentriaSCServiceDTO::LoadConfiguration start");

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            //FastCGIListener
            if(settings.contains("FastCGIListener"))
            {
                FastCGIListener = settings.value("FastCGIListener").toString();
                SCLog::AddDebug(QString("FastCGIListener=%1").arg(FastCGIListener.simplified()));
            }
            else
            {
                SCLog::AddError("FastCGIListener is not defined in config.ini file");
            }

            //PlatformClient
            if(settings.contains("PlatformClient"))
            {
                PlatformClient = settings.value("PlatformClient").toString();
                SCLog::AddDebug(QString("PlatformClient=%1").arg(PlatformClient.simplified()));
            }
            else
            {
                SCLog::AddError("PlatformClient is not defined in config.ini file");
            }

            //CentriaTCPServer
            if(settings.contains("CentriaTCPServer"))
            {
                CentriaTCPServer = settings.value("CentriaTCPServer").toString();
                SCLog::AddDebug(QString("CentriaTCPServer=%1").arg(CentriaTCPServer.simplified()));
            }
            else
            {
                SCLog::AddError("CentriaTCPServer is not defined in config.ini file");
            }

            //CentriaTCPClient
            if(settings.contains("CentriaTCPClient"))
            {
                CentriaTCPClient = settings.value("CentriaTCPClient").toString();
                SCLog::AddDebug(QString("CentriaTCPClient=%1").arg(CentriaTCPClient.simplified()));
            }
            else
            {
                SCLog::AddError("CentriaTCPClient is not defined in config.ini file");
            }

        }
    }

    SCLog::AddDebug("CentriaSCServiceDTO::LoadConfiguration end");
}
