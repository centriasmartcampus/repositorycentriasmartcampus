#include "mainwindow.h"
#include <QApplication>
#include <signal.h>

void signalhandler(int sig)
{
    if(sig == SIGINT)
    {
        qApp->quit();
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signalhandler);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
