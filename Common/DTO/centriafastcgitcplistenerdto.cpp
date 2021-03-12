#include "centriafastcgitcplistenerdto.h"

CentriaFastCGITCPListenerDTO::CentriaFastCGITCPListenerDTO()
{

}

CentriaFastCGITCPListenerDTO::CentriaFastCGITCPListenerDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaFastCGITCPListenerDTO::CentriaFastCGITCPListenerDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaFastCGITCPListenerDTO::CentriaFastCGITCPListenerDTO(%1) end").arg(id));
}

void CentriaFastCGITCPListenerDTO::LoadConfiguration()
{
    SCLog::AddDebug(QString("CentriaFastCGITCPListenerDTO::LoadConfiguration(%1) start").arg(ID));

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            if(settings.contains("TCPPort"))
            {
                TCPPort = settings.value("TCPPort").toInt();
                SCLog::AddDebug(QString("TCPPort=%1").arg(TCPPort));
            }
            else
            {
                SCLog::AddError("TCPPort is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug(QString("CentriaFastCGITCPListenerDTO::LoadConfiguration(%1) start").arg(ID));
}
