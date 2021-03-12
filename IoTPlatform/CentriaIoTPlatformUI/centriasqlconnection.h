#ifndef CENTRIASQLCONNECTION_H
#define CENTRIASQLCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QUuid>
#include <QSqlRecord>
#include <QSqlError>

#include "DTO/centriasqlconnectiondto.h"
#include "Entities/sqlobject.h"
#include "Entities/sqlobjecthierarchy.h"

class CentriaSQLConnection : public QObject
{
    Q_OBJECT
public:
    CentriaSQLConnectionDTO DTO;

    explicit CentriaSQLConnection(QString id, QObject *parent = nullptr);
    ~CentriaSQLConnection();

    QMap<QUuid, SQLObject> GetObjects();
    QMap<quint64,SQLObjectHierarchy> GetObjectHierarchies();

    void AddNewObjectHierarchy(SQLObjectHierarchy sqlObjectHierarchy);
    void DeleteObjectHierarchy(quint64 id);

signals:

public slots:

private:
    QSqlDatabase _database;
};

#endif // CENTRIASQLCONNECTION_H
