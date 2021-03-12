#include "dialogcreateobject.h"
#include "ui_dialogcreateobject.h"

DialogCreateObject::DialogCreateObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateObject)
{
    ui->setupUi(this);
}

DialogCreateObject::~DialogCreateObject()
{
    delete ui;
}

void DialogCreateObject::on_buttonBox_accepted()
{
    QString objectName =  ui->lineEditObjectName->text();

    if(objectName.size() > 0)
    {
        SQLObjectValue.Name = objectName;
        SQLObjectHierarchyValue.Name = objectName;
    }
    else
    {
        reject();
    }
}
