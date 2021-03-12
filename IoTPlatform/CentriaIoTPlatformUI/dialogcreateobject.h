#ifndef DIALOGCREATEOBJECT_H
#define DIALOGCREATEOBJECT_H

#include <QDialog>

#include "Entities/sqlobject.h"
#include "Entities/sqlobjecthierarchy.h"

namespace Ui {
class DialogCreateObject;
}

class DialogCreateObject : public QDialog
{
    Q_OBJECT

public:
    SQLObject SQLObjectValue;
    SQLObjectHierarchy SQLObjectHierarchyValue;

    explicit DialogCreateObject(QWidget *parent = 0);
    ~DialogCreateObject();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogCreateObject *ui;
};

#endif // DIALOGCREATEOBJECT_H
