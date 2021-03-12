#ifndef SCLOG_H
#define SCLOG_H

#include <QString>
#include <QDebug>
#include <QDateTime>

#include <iostream>

#define MAX_LINE_SIZE 500


class SCLog
{
public:
    static void AddDebug(QString text)
    {
        QString logText(QString("%1 : (DEBUG) %2").arg(QDateTime::currentDateTimeUtc().toString("yy-MM-dd hh:mm:ss:zzz")).arg(text));
        WriteLog(logText);
    }

    static void AddLog(QString text)
    {
        QString logText(QString("%1 : (LOG) %2").arg(QDateTime::currentDateTimeUtc().toString("yy-MM-dd hh:mm:ss:zzz")).arg(text));
        WriteLog(logText);
    }

    static void AddError(QString text)
    {
        QString logText(QString("%1 : (ERROR) %2").arg(QDateTime::currentDateTimeUtc().toString("yy-MM-dd hh:mm:ss:zzz")).arg(text));
        WriteLog(logText);
    }

    static void AddWarning(QString text)
    {
        QString logText(QString("%1 : (WARNING) %2").arg(QDateTime::currentDateTimeUtc().toString("yy-MM-dd hh:mm:ss:zzz")).arg(text));
        WriteLog(logText);
    }

private:
    static void WriteLog(QString& logText)
    {
        if(logText.size() > MAX_LINE_SIZE)
        {
            logText = logText.mid(0, MAX_LINE_SIZE) + "...";
        }
        std::cout << logText.toUtf8().data() << "\n";
    }

};

#endif // SCLOG_H
