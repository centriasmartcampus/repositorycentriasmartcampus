#ifndef SQLATTRIBUTEVALUEPARSER_H
#define SQLATTRIBUTEVALUEPARSER_H

#include <QObject>
#include <QVariant>


class SQLAttributeValueParser
{
public:
    SQLAttributeValueParser();

    static QVariant GetAttributeValue(QString valueType, QByteArray value);
    static QByteArray CreateByteArray(QString valueType, QString value);
};

#endif // SQLATTRIBUTEVALUEPARSER_H
