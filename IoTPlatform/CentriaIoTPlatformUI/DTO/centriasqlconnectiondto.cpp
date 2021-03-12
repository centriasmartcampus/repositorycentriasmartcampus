#include "centriasqlconnectiondto.h"

CentriaSQLConnectionDTO::CentriaSQLConnectionDTO()
{

}

CentriaSQLConnectionDTO::CentriaSQLConnectionDTO(QString id)
{
    SCLog::AddDebug(QString("CentriaSQLConnectionDTO::CentriaSQLConnectionDTO(%1) start").arg(id));
    ID = id;
    LoadConfiguration();
    SCLog::AddDebug(QString("CentriaSQLConnectionDTO::CentriaSQLConnectionDTO(%1) end").arg(id));
}

void CentriaSQLConnectionDTO::LoadConfiguration()
{
    SCLog::AddDebug("CentriaSQLConnectionDTO::LoadConfiguration start");

    QString configFile = QCoreApplication::applicationDirPath() + "/config.ini";
    QSettings settings(configFile, QSettings::IniFormat);
    QStringList childGroups = settings.childGroups();
    foreach(QString group, childGroups)
    {
        if(group == ID)
        {
            settings.beginGroup(group);

            if(settings.contains("MySQLHostName"))
            {
                MySQLHostName = settings.value("MySQLHostName").toString();
                SCLog::AddDebug(QString("MySQLHostName=%1").arg(MySQLHostName.simplified()));
            }
            else
            {
                SCLog::AddError("MySQLHostName is not defined in config.ini file");
            }

            if(settings.contains("MySQLDatabaseName"))
            {
                MySQLDatabaseName = settings.value("MySQLDatabaseName").toString();
                SCLog::AddDebug(QString("MySQLDatabaseName=%1").arg(MySQLDatabaseName.simplified()));
            }
            else
            {
                SCLog::AddError("MySQLDatabaseName is not defined in config.ini file");
            }

            if(settings.contains("MySQLUserName"))
            {
                MySQLUserName = settings.value("MySQLUserName").toString();
                SCLog::AddDebug(QString("MySQLUserName=%1").arg(MySQLUserName.simplified()));
            }
            else
            {
                SCLog::AddError("MySQLUserName is not defined in config.ini file");
            }

            if(settings.contains("MySQLPassword"))
            {
                MySQLPassword = settings.value("MySQLPassword").toString();
                SCLog::AddDebug(QString("MySQLPassword=%1").arg(MySQLPassword.simplified()));
            }
            else
            {
                SCLog::AddError("MySQLPassword is not defined in config.ini file");
            }
        }
    }

    SCLog::AddDebug("CentriaSQLConnectionDTO::LoadConfiguration end");
}
