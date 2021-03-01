#include "sctcplistenerdto.h"

SCTCPListenerDTO::SCTCPListenerDTO()
{

}

SCTCPListenerDTO::SCTCPListenerDTO(QString id)
{
    SCLog::AddDebug(QString("SCTCPListenerDTO::SCTCPListenerDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("SCTCPListenerDTO::SCTCPListenerDTO(%1) end").arg(id));
}

void SCTCPListenerDTO::LoadConfiguration()
{
    SCLog::AddDebug(QString("SCTCPListenerDTO::LoadConfiguration(%1) start").arg(ID));

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

    SCLog::AddDebug(QString("SCTCPListenerDTO::LoadConfiguration(%1) start").arg(ID));
}
