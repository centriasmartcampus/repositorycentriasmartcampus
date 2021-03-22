#ifndef SQLATTRIBUTEVALUE_H
#define SQLATTRIBUTEVALUE_H

#include <QObject>

class SQLAttributeValue
{
public:
    quint64 ID = 0;
    quint64 AttributeID = 0;
    QUuid ObjectUUID = "";
    QByteArray Value;
};

#endif // SQLATTRIBUTEVALUE_H
