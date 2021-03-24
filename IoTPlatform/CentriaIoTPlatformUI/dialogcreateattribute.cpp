#include "dialogcreateattribute.h"
#include "ui_dialogcreateattribute.h"

DialogCreateAttribute::DialogCreateAttribute(CentriaSQLConnection *centriaSQLConnection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateAttribute)
{

    _centriaSQLConnection = centriaSQLConnection;
    ui->setupUi(this);

    ui->comboBoxAttributeValueType->addItem("bool");
    ui->comboBoxAttributeValueType->addItem("int");
    ui->comboBoxAttributeValueType->addItem("decimal");
    ui->comboBoxAttributeValueType->addItem("string");
    ui->comboBoxAttributeValueType->addItem("binary");
}

DialogCreateAttribute::~DialogCreateAttribute()
{
    delete ui;
}

void DialogCreateAttribute::on_buttonBox_accepted()
{
    if(_centriaSQLConnection != nullptr)
    {
        NewSQLAttribute.Name = ui->lineEditAttributeName->text();
        NewSQLAttribute.ValueType = ui->comboBoxAttributeValueType->currentText();

        _centriaSQLConnection->AddNewAttribute(NewSQLAttribute);
    }
}
