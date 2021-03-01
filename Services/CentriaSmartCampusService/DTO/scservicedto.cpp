#include "scservicedto.h"

SCServiceDTO::SCServiceDTO()
{

}

SCServiceDTO::SCServiceDTO(QString id)
{
    SCLog::AddDebug(QString("SCServiceDTO::SCServiceDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("SCServiceDTO::SCServiceDTO(%1) end").arg(id));
}

void SCServiceDTO::LoadConfiguration()
{
    SCLog::AddDebug("SCServiceDTO::LoadConfiguration start");

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            if(settings.contains("TCPListener"))
            {
                TCPListener = settings.value("TCPListener").toString();
                SCLog::AddDebug(QString("TCPListener=%1").arg(TCPListener.simplified()));
            }
            else
            {
                SCLog::AddError("TCPListener is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug("SCServiceDTO::LoadConfiguration end");
}
