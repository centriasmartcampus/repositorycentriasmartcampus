#include <QCoreApplication>
#include "centriascservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CentriaSCService centriaSCService(&a);

    return a.exec();
}
