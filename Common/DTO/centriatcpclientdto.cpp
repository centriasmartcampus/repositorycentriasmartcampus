#include "centriatcpclientdto.h"

CentriaTCPClientDTO::CentriaTCPClientDTO()
{

}

CentriaTCPClientDTO::CentriaTCPClientDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaTCPClientDTO::CentriaTCPClientDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaTCPClientDTO::CentriaTCPClientDTO(%1) end").arg(id));
}

void CentriaTCPClientDTO::LoadConfiguration()
{
    SCLog::AddDebug(QString("CentriaTCPClientDTO::LoadConfiguration(%1) start").arg(ID));

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
                SCLog::AddDebug(QString("IPAddress=%1").arg(IPAddress));
            }
            else
            {
                SCLog::AddError("IPAddress is not defined in config.ini file");
            }

            //Port
            if(settings.contains("Port"))
            {
                Port = settings.value("Port").toInt();
                SCLog::AddDebug(QString("Port=%1").arg(Port));
            }
            else
            {
                SCLog::AddError("Port is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug(QString("CentriaTCPClientDTO::LoadConfiguration(%1) start").arg(ID));
}
