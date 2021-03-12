#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "signal.h"

#include "scservice.h"

void signalhandler(int sig)
{
    if(sig == SIGINT)
    {
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //signal(SIGINT, signalhandler);
    SCService scService(&a);
    return a.exec();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
