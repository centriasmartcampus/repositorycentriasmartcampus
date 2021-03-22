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
#include "Entities/sqlattribute.h"
#include "Entities/sqlattributevalue.h"

class CentriaSQLConnection : public QObject
{
    Q_OBJECT
public:
    CentriaSQLConnectionDTO DTO;

    explicit CentriaSQLConnection(QString id, QObject *parent = nullptr);
    ~CentriaSQLConnection();

    QMap<QUuid, SQLObject> GetObjects();
    QMap<quint64,SQLObjectHierarchy> GetObjectHierarchies();
    QMap<quint64, SQLAttribute> GetAttributes();
    QMap<quint64, SQLAttributeValue> GetObjectAttributeValues(QUuid objectUUID);

    void AddNewObjectHierarchy(SQLObjectHierarchy& sqlObjectHierarchy);
    void AddNewObject(SQLObject& sqlObject);
    void AddNewAttribute(SQLAttribute & sqlAttribute);
    void AddNewAttributeValue(SQLAttributeValue &sqlAttributeValue);
    void DeleteObjectHierarchy(quint64 id);
    void UpdateObjectHierarchy(SQLObjectHierarchy& sqlObjectHierarchy);



signals:

public slots:

private:
    QSqlDatabase _database;
};

#endif // CENTRIASQLCONNECTION_H
