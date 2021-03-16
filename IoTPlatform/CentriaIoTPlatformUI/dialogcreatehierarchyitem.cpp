#include "dialogcreatehierarchyitem.h"
#include "ui_dialogcreatehierarchyitem.h"

DialogCreateHierarchyItem::DialogCreateHierarchyItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateHierarchyItem)
{
    ui->setupUi(this);

    this->setWindowTitle("Crete new hierarchy item");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create new item");
}

DialogCreateHierarchyItem::~DialogCreateHierarchyItem()
{
    delete ui;
}

void DialogCreateHierarchyItem::on_buttonBox_accepted()
{
    Name =  ui->lineEditHierarchyItemName->text();

    if(Name.size() == 0)
    {
        reject();
    }
}
