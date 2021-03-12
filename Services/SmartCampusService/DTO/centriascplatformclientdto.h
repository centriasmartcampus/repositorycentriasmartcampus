#ifndef CENTRIASCPLATFORMCLIENTDTO_H
#define CENTRIASCPLATFORMCLIENTDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaSCPlatformClientDTO
{
public:
    QString ID = "";
    QString IPAddress = "";
    quint16 Port = 0;
    bool AcceptSelfSignedCertificates = false;

    CentriaSCPlatformClientDTO();
    CentriaSCPlatformClientDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIASCPLATFORMCLIENTDTO_H
