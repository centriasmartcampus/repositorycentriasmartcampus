#ifndef SQLATTRIBUTEVALUE_H
#define SQLATTRIBUTEVALUE_H

#include <QObject>

#include "sqlattribute.h"

class SQLAttributeValue
{
public:
    quint64 ID = 0;
    quint64 AttributeID = 0;
    QUuid ObjectUUID = "";
    QByteArray Value;
    SQLAttribute Attribute;
};
Q_DECLARE_METATYPE(SQLAttributeValue)

#endif // SQLATTRIBUTEVALUE_H
