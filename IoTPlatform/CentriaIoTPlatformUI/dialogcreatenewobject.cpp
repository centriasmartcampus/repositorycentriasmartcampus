#include "dialogcreatenewobject.h"
#include "ui_dialogcreatenewobject.h"

DialogCreateNewObject::DialogCreateNewObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateNewObject)
{
    ui->setupUi(this);
}

DialogCreateNewObject::~DialogCreateNewObject()
{
    delete ui;
}

void DialogCreateNewObject::on_pushButtonCreateNewUUID_clicked()
{
    QUuid uuid = QUuid::createUuid();
    ui->lineEditUUID->setText(uuid.toString(QUuid::WithoutBraces));
}

void DialogCreateNewObject::on_buttonBox_accepted()
{
    Name = ui->lineEditObjectName->text();
    UUID = QUuid(ui->lineEditUUID->text());
}
