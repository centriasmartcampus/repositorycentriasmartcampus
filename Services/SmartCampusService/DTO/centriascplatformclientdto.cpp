#include "centriascplatformclientdto.h"

CentriaSCPlatformClientDTO::CentriaSCPlatformClientDTO()
{

}

CentriaSCPlatformClientDTO::CentriaSCPlatformClientDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaSCPlatformClientDTO::CentriaSCPlatformClientDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaSCPlatformClientDTO::CentriaSCPlatformClientDTO(%1) end").arg(id));
}

void CentriaSCPlatformClientDTO::LoadConfiguration()
{
    SCLog::AddDebug("CentriaSCPlatformClientDTO::LoadConfiguration start");

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            //IPAddress
            if(settings.contains("IPAddress"))
            {
                IPAddress = settings.value("IPAddress").toString();
                SCLog::AddDebug(QString("IPAddress=%1").arg(IPAddress.simplified()));
            }
            else
            {
                SCLog::AddError("IPAddress is not defined in config.ini file");
            }

            //Port
            if(settings.contains("Port"))
            {
                Port = settings.value("Port").toUInt();
                SCLog::AddDebug(QString("Port=%1").arg(Port));
            }
            else
            {
                SCLog::AddError("Port is not defined in config.ini file");
            }

            //AcceptSelfSignedCertificates
            if(settings.contains("AcceptSelfSignedCertificates"))
            {
                AcceptSelfSignedCertificates = settings.value("Port").toBool();
                SCLog::AddDebug(QString("AcceptSelfSignedCertificates=%1").arg(AcceptSelfSignedCertificates));
            }
            else
            {
                SCLog::AddError("AcceptSelfSignedCertificates is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug("CentriaSCPlatformClientDTO::LoadConfiguration end");
}
