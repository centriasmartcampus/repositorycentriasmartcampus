#ifndef CENTRIATCPCLIENTDTO_H
#define CENTRIATCPCLIENTDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaTCPClientDTO
{
public:
    QString ID = "";
    QString IPAddress = "";
    ushort Port = 0;

    CentriaTCPClientDTO();
    CentriaTCPClientDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIATCPCLIENTDTO_H
