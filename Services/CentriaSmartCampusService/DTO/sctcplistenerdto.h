#ifndef SCTCPLISTENERDTO_H
#define SCTCPLISTENERDTO_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class SCTCPListenerDTO
{
public:
    QString ID = "";
    ushort TCPPort = 0;

    SCTCPListenerDTO();
    SCTCPListenerDTO(QString id);

private:
    void LoadConfiguration();
};


#endif // SCTCPLISTENERDTO_H
