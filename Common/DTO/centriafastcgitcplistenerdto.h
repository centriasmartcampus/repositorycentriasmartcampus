#ifndef CENTRIAFASTCGITCPLISTENERDTO_H
#define CENTRIAFASTCGITCPLISTENERDTO_H


#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "sclog.h"

class CentriaFastCGITCPListenerDTO
{
public:
    QString ID = "";
    ushort TCPPort = 0;

    CentriaFastCGITCPListenerDTO();
    CentriaFastCGITCPListenerDTO(QString id);

private:
    void LoadConfiguration();
};



#endif // CENTRIAFASTCGITCPLISTENERDTO_H
