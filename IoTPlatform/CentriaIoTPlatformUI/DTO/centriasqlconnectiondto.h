#ifndef CENTRIASQLCONNECTIONDTO_H
#define CENTRIASQLCONNECTIONDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaSQLConnectionDTO
{
public:
    QString ID = "";
    QString MySQLHostName = "";
    QString MySQLDatabaseName = "";
    QString MySQLUserName= "";
    QString MySQLPassword = "";

    CentriaSQLConnectionDTO();
    CentriaSQLConnectionDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIASQLCONNECTIONDTO_H
