#ifndef SQLOBJECT_H
#define SQLOBJECT_H

#include <QObject>
#include <QUuid>

class SQLObject
{
public:
    QUuid ObjectUUID = "";
    QString Name = "";
};

#endif // SQLOBJECT_H
