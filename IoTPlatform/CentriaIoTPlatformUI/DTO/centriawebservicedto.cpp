#include "centriawebservicedto.h"

CentriaWebServiceDTO::CentriaWebServiceDTO()
{

}

CentriaWebServiceDTO::CentriaWebServiceDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaWebServiceDTO::CentriaWebServiceDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaWebServiceDTO::CentriaWebServiceDTO(%1) end").arg(id));
}

void CentriaWebServiceDTO::LoadConfiguration()
{
    SCLog::AddDebug("CentriaWebServiceDTO::LoadConfiguration start");

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            if(settings.contains("CentriaFastCGITCPListener"))
            {
                CentriaFastCGITCPListener = settings.value("CentriaFastCGITCPListener").toString();
                SCLog::AddDebug(QString("CentriaFastCGITCPListener=%1").arg(CentriaFastCGITCPListener.simplified()));
            }
            else
            {
                SCLog::AddError("CentriaFastCGITCPListener is not defined in config.ini file");
            }

            if(settings.contains("CentriaSQLConnection"))
            {
                CentriaSQLConnection = settings.value("CentriaSQLConnection").toString();
                SCLog::AddDebug(QString("CentriaSQLConnection=%1").arg(CentriaSQLConnection.simplified()));
            }
            else
            {
                SCLog::AddError("CentriaSQLConnection is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug("CentriaWebServiceDTO::LoadConfiguration end");
}
