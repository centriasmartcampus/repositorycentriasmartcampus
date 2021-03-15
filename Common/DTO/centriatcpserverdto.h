#ifndef CENTRIATCPSERVERDTO_H
#define CENTRIATCPSERVERDTO_H


#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaTCPServerDTO
{
public:
    QString ID = "";
    ushort TCPPort = 0;

    CentriaTCPServerDTO();
    CentriaTCPServerDTO(QString id);

private:
    void LoadConfiguration();
};


#endif // CENTRIATCPSERVERDTO_H
