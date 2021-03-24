#include "sqlattributevalueparser.h"

SQLAttributeValueParser::SQLAttributeValueParser()
{

}

QVariant SQLAttributeValueParser::GetAttributeValue(QString valueType, QByteArray value)
{
    QVariant parsedValue = value;

    if(valueType == "bool")
    {
        parsedValue = value.toStdString() == "true";
    }
    else if(valueType == "int")
    {
        parsedValue = value.toInt();
    }
    else if(valueType == "decimal")
    {
        parsedValue = value.toDouble();
    }
    else if(valueType == "string")
    {
        parsedValue = QString::fromStdString(value.toStdString());
    }

    return parsedValue;
}

QByteArray SQLAttributeValueParser::CreateByteArray(QString valueType, QString value)
{
    QByteArray bytearrayValue;

    if(valueType == "bool")
    {
        bytearrayValue = value.toLower() == "true" ? QString("true").toUtf8().data() :QString("false").toUtf8().data();
    }
    else if(valueType == "int")
    {
        bytearrayValue = value.toUtf8().data();
    }
    else if(valueType == "decimal")
    {
        bytearrayValue = value.toUtf8().data();
    }
    else if(valueType == "string")
    {
        bytearrayValue = value.toUtf8().data();
    }

    return bytearrayValue;
}

