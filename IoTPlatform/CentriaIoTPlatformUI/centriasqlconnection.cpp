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
                sqlObject.ObjectUUID = record.value("ObjectUUID").toByteArray();
                sqlObject.Name = record.value("Name").toString();
                sqlObjects.insert(sqlObject.ObjectUUID, sqlObject);
            }
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjects%1) end").arg(DTO.ID));
    return sqlObjects;
}

QMap<quint64,SQLObjectHierarchy> CentriaSQLConnection::GetObjectHierarchies()
{
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectHierarchies%1) start").arg(DTO.ID));
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
                sqlObjectHierarchy.ObjectUUID = record.value("ObjectUUID").toByteArray();
                sqlObjectHierarchy.Name = record.value("Name").toString();
                sqlObjectHiearchies.insert(sqlObjectHierarchy.ID, sqlObjectHierarchy);
            }
        }
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::GetObjectHierarchies%1) end").arg(DTO.ID));
    return sqlObjectHiearchies;
}

void CentriaSQLConnection::AddNewObjectHierarchy(SQLObjectHierarchy& sqlObjectHierarchy)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObjectHierarchy%1) start").arg(DTO.ID));
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
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::AddNewObjectHierarchy%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::DeleteObjectHierarchy(quint64 id)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::DeleteObjectHierarchy%1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString deleteQuery = QString("DELETE FROM ObjectHierarchy WHERE ID=:ID");
    query.prepare(deleteQuery);
    query.bindValue(":ID", id);
    if(!query.exec())
    {
        SCLog::AddError(QString("Cannot delete hierarchy(ID=%1)) object from database").arg(id));
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::DeleteObjectHierarchy%1) end").arg(DTO.ID));
}

void CentriaSQLConnection::UpdateObjectHierarchy(SQLObjectHierarchy &sqlObjectHierarchy)
{
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateObjectHierarchy %1) start").arg(DTO.ID));
    QSqlQuery query(_database);
    QString updateQuery = QString("UPDATE ObjectHierarchy SET ParentID=:parentID, Name=:name, ObjectUUID=:objectUUID WHERE ID=%1;").arg(sqlObjectHierarchy.ID);
    query.prepare(updateQuery);
    query.bindValue(":parentID", sqlObjectHierarchy.ParentID);
    query.bindValue(":name", sqlObjectHierarchy.Name);
    query.bindValue(":objectUUID", sqlObjectHierarchy.ObjectUUID.toByteArray(), QSql::In | QSql::Binary);
    //query.prepare("INSERT INTO Object (ObjectUUID, Name) VALUES( :data, 'Service')");
    //query.bindValue(":data", uuid.toByteArray(), QSql::In | QSql::Binary);
    if(!query.exec())
    {
        SCLog::AddError("Cannot updatehierarchy object to database");
        SCLog::AddError(query.lastError().text());
    }
    SCLog::AddDebug(QString("CentriaSQLConnection::UpdateObjectHierarchy %1) end").arg(DTO.ID));
}


