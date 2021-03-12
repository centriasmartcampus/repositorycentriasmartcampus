#ifndef CENTRIAWEBSERVICEDTO_H
#define CENTRIAWEBSERVICEDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaWebServiceDTO
{
public:
    QString ID = "";
    QString CentriaFastCGITCPListener = "";
    QString CentriaSQLConnection = "";

    CentriaWebServiceDTO();
    CentriaWebServiceDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIAWEBSERVICEDTO_H
