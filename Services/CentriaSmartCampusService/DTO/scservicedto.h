#ifndef SCSERVICEDTO_H
#define SCSERVICEDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class SCServiceDTO
{
public:
    QString ID = "";
    QString TCPListener = "";

    SCServiceDTO();
    SCServiceDTO(QString id);

private:
    void LoadConfiguration();
};

#endif // SCSERVICEDTO_H
