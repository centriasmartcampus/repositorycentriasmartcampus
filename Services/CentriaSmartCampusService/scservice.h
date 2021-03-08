#ifndef SCSERVICE_H
#define SCSERVICE_H

#include <QObject>

#include "sclog.h"
#include "DTO/scservicedto.h"
#include "sctcplistener.h"

class SCService : public QObject
{
    Q_OBJECT
public:
    SCServiceDTO DTO;
    explicit SCService(QObject *parent = nullptr);
    ~SCService();

signals:


public slots:
    void NewRequest(SCFastCGIRequest& scFastCGIRequest);

private:
    SCTCPListener *_scTCPListener = nullptr;


};

#endif // SCSERVICE_H
