#ifndef CENTRIASCSERVICEDTO_H
#define CENTRIASCSERVICEDTO_H


#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaSCServiceDTO
{
public:
    QString ID = "";
    QString FastCGIListener = "";
    QString PlatformClient = "";
    QString CentriaTCPServer = "";
    QString CentriaTCPClient = "";

    CentriaSCServiceDTO();
    CentriaSCServiceDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIASCSERVICEDTO_H
