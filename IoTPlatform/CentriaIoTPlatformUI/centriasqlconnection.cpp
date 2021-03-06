#include "centriasqlconnection.h"


CentriaSQLConnection::CentriaSQLConnection(QString id, QObject *parent)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::CentriaSQLConnection(%1) start").arg(id));
    DTO = CentriaSQLConnectionDTO(id);
    if(DTO.MySQLDatabaseName.size() > 0)
    {
        if(DTO.MySQLHostName.size() > 0)
        {
            if(DTO.MySQLUserName.size() > 0 && DTO.MySQLPassword.size() > 0)
            {
                _database = QSqlDatabase::addDatabase("QMYSQL");
                _database.setHostName(DTO.MySQLHostName);
                _database.setDatabaseName(DTO.MySQLDatabaseName);
                _database.setUserName(DTO.MySQLUserName);
                _database.setPassword(DTO.MySQLPassword);
            }
            else
            {
                SCLog::AddError(QString("Canot set user name or password to QSqlDatabase. MySQLUserName or MySQLPassword is missing."));
            }

        }
        else
        {
            SCLog::AddError(QString("Canot set host name to QSqlDatabase. MySQLHostName is missing."));
        }
    }
    else
    {
        SCLog::AddError(QString("Canot create QSqlDatabase. MySQLDatabaseName is missing."));
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::CentriaSQLConnection(%1) end").arg(id));

}

CentriaSQLConnection::~CentriaSQLConnection()
{
    SCLog::AddDebug(QString("CentriaSQLConnection::~CentriaSQLConnection(%1) start").arg(DTO.ID));
    _database.close();
    SCLog::AddDebug(QString("CentriaSQLConnection::~CentriaSQLConnection(%1) end").arg(DTO.ID));
}

 QMap<QUuid, SQLObject> CentriaSQLConnection::GetObjects()
{
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjects%1) start").arg(DTO.ID));
    QMap<QUuid, SQLObject> sqlObjects;
    if(_database.open())
    {
        QSqlQuery query(_database);

        QString queryString = QString("SELECT ObjectUUID, Name FROM Object");
        if(query.exec(queryString))
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                SQLObject sqlObject;
                sqlObject.ObjectUUID = QUuid::fromRfc4122(record.value("ObjectUUID").toByteArray());
                sqlObject.Name = record.value("Name").toString();
                sqlObjects.insert(sqlObject.ObjectUUID, sqlObject);
            }
        }
        else
        {
            SCLog::AddError("Cannot get hierarchy objects from database");
            SCLog::AddError(query.lastError().text());
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjects%1) end").arg(DTO.ID));
    return sqlObjects;
}

QMap<quint64,SQLObjectHierarchy> CentriaSQLConnection::GetObjectHierarchies()
{
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectHierarchies(%1) start").arg(DTO.ID));
    QMap<quint64,SQLObjectHierarchy> sqlObjectHiearchies;
    if(_database.open())
    {
        QSqlQuery query(_database);

        QString selectQuery = QString("SELECT ID, ParentID, Name, ObjectUUID FROM ObjectHierarchy ORDER BY ParentID");
        if(query.exec(selectQuery))
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                SQLObjectHierarchy sqlObjectHierarchy;
                sqlObjectHierarchy.ID = record.value("ID").toULongLong();
                sqlObjectHierarchy.ParentID = record.value("ParentID").toULongLong();
                sqlObjectHierarchy.ObjectUUID = QUuid::fromRfc4122(record.value("ObjectUUID").toByteArray());
                sqlObjectHierarchy.Name = record.value("Name").toString();
                sqlObjectHiearchies.insert(sqlObjectHierarchy.ID, sqlObjectHierarchy);
            }
        }
        else
        {

            SCLog::AddError("Cannot get objects from database");
            SCLog::AddError(query.lastError().text());
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectHierarchies(%1) end").arg(DTO.ID));
    return sqlObjectHiearchies;
}

QMap<quint64, SQLAttribute> CentriaSQLConnection::GetAttributes()
{
    SCLog::AddDebug(QString("CentriaSQLConnection::GetAttributes(%1) start").arg(DTO.ID));
    QMap<quint64,SQLAttribute> sqlAttributes;
    if(_database.open())
    {
        QSqlQuery query(_database);

        QString selectQuery = QString("SELECT ID, Name, ValueType FROM Attribute ORDER BY Name");
        if(query.exec(selectQuery))
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                SQLAttribute sqlAttribute;
                sqlAttribute.ID = record.value("ID").toULongLong();
                sqlAttribute.Name = record.value("Name").toString();
                sqlAttribute.ValueType = record.value("ValueType").toString();
                sqlAttributes.insert(sqlAttribute.ID, sqlAttribute);
            }
        }
        else
        {
            SCLog::AddError("Cannot get attributes from database");
            SCLog::AddError(query.lastError().text());
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetAttributes(%1) end").arg(DTO.ID));
    return sqlAttributes;
}

QMap<quint64, SQLAttributeValue> CentriaSQLConnection::GetObjectAttributeValues(QUuid objectUUID)
{    
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectAttributeValues(%1) start").arg(DTO.ID));
    QMap<quint64,SQLAttributeValue> sqlAttributeValues;
    if(_database.open())
    {
        QSqlQuery query(_database);

        QString selectQuery = QString("SELECT ID, AttributeID, ObjectUUID, Value FROM AttributeValue WHERE ObjectUUID=:objectUUID");
        query.prepare(selectQuery);
        query.bindValue(":objectUUID", objectUUID.toRfc4122(), QSql::In | QSql::Binary);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                SQLAttributeValue sqlAttributeValue;
                sqlAttributeValue.ID = record.value("ID").toULongLong();
                sqlAttributeValue.AttributeID = record.value("AttributeID").toULongLong();
                sqlAttributeValue.ObjectUUID = QUuid::fromRfc4122(record.value("ObjectUUID").toByteArray());
                sqlAttributeValue.Value = record.value("Value").toByteArray();
                sqlAttributeValues.insert(sqlAttributeValue.ID, sqlAttributeValue);
            }
        }
        else
        {
            SCLog::AddError("Cannot get attribute values from database");
            SCLog::AddError(query.lastError().text());
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectAttributeValues(%1) end").arg(DTO.ID));
    return sqlAttributeValues;
}

void CentriaSQLConnection::AddNewObjectHierarchy(SQLObjectHierarchy& sqlObjectHierarchy)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObjectHierarchy(%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString insertQuery = QString("INSERT INTO ObjectHierarchy(ParentID, Name) VALUES(:parentID, :name)");
    query.prepare(insertQuery);
    query.bindValue(":parentID", sqlObjectHierarchy.ParentID);
    query.bindValue(":name", sqlObjectHierarchy.Name);
    //query.prepare("INSERT INTO Object (ObjectUUID, Name) VALUES( :data, 'Service')");
    //query.bindValue(":data", uuid.toByteArray(), QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot add new hierarchy object to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObjectHierarchy(%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::AddNewObject(SQLObject &sqlObject)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObject(%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString insertQuery = QString("INSERT INTO Object(Name, ObjectUUID) VALUES(:name, :objectUUID)");
    query.prepare(insertQuery);
    query.bindValue(":name", sqlObject.Name);
    query.bindValue(":objectUUID", sqlObject.ObjectUUID.toRfc4122(), QSql::In | QSql::Binary);
    //query.prepare("INSERT INTO Object (ObjectUUID, Name) VALUES( :data, 'Service')");
    //query.bindValue(":data", uuid.toByteArray(), QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot add new object to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObject(%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::AddNewAttribute(SQLAttribute &sqlAttribute)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewAttribute(%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString insertQuery = QString("INSERT INTO Attribute(Name, ValueType) VALUES(:name, :valueType)");
    query.prepare(insertQuery);
    query.bindValue(":name", sqlAttribute.Name);
    query.bindValue(":valueType", sqlAttribute.ValueType);
    if(!query.exec())
    {
        SCLog::AddError("Cannot add new attribute to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewAttribute(%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::AddNewAttributeValue(SQLAttributeValue &sqlAttributeValue)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewAttributeValue(%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString insertQuery = QString("INSERT INTO AttributeValue(AttributeID, ObjectUUID,Value) VALUES(:attributeID, :objectUUID, :value)");
    query.prepare(insertQuery);
    query.bindValue(":attributeID", sqlAttributeValue.AttributeID);
    query.bindValue(":objectUUID", sqlAttributeValue.ObjectUUID.toRfc4122(), QSql::In | QSql::Binary);
    query.bindValue(":value", sqlAttributeValue.Value, QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot add new attribute to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewAttributeValue(%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::DeleteObjectHierarchy(quint64 id)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::DeleteObjectHierarchy(%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString deleteQuery = QString("DELETE FROM ObjectHierarchy WHERE ID=:ID");
    query.prepare(deleteQuery);
    query.bindValue(":ID", id);
    if(!query.exec())
    {
        SCLog::AddError(QString("Cannot delete hierarchy(ID=%1)) object from database").arg(id));
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::DeleteObjectHierarchy(%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::UpdateObjectHierarchy(SQLObjectHierarchy &sqlObjectHierarchy)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateObjectHierarchy (%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString updateQuery = QString("UPDATE ObjectHierarchy SET ParentID=:parentID, Name=:name, ObjectUUID=:objectUUID WHERE ID=%1;").arg(sqlObjectHierarchy.ID);
    query.prepare(updateQuery);
    query.bindValue(":parentID", sqlObjectHierarchy.ParentID);
    query.bindValue(":name", sqlObjectHierarchy.Name);
    query.bindValue(":objectUUID", sqlObjectHierarchy.ObjectUUID.toRfc4122(), QSql::In | QSql::Binary);
    //query.prepare("INSERT INTO Object (ObjectUUID, Name) VALUES( :data, 'Service')");
    //query.bindValue(":data", uuid.toByteArray(), QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot updatehierarchy object to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateObjectHierarchy (%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::UpdateAttributeValue(SQLAttributeValue &sqlAttributeValue)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateAttributeValue (%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString updateQuery = QString("UPDATE AttributeValue SET Value=:value WHERE ID=%1;").arg(sqlAttributeValue.ID);
    query.prepare(updateQuery);
    query.bindValue(":value", sqlAttributeValue.Value, QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot Attribute Value to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateAttributeValue (%1) end").arg(DTO.ID));
}


