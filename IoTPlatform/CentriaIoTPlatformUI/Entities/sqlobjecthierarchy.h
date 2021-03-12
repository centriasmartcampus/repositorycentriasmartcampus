#ifndef SQLOBJECTHIERARCHY_H
#define SQLOBJECTHIERARCHY_H

#include <QObject>
#include <QUuid>

class SQLObjectHierarchy
{
public:
    quint64 ID = 0;
    quint64 ParentID = 0;
    QString Name = "";
    QUuid ObjectUUID = "";

};

#endif // SQLOBJECTHIERARCHY_H
