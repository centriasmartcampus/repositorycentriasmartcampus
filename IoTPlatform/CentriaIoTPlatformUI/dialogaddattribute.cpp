#include "dialogaddattribute.h"
#include "ui_dialogaddattribute.h"

DialogAddAttribute::DialogAddAttribute(CentriaSQLConnection *centriaSQLConnection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddAttribute)
{
    _centriaSQLConnection = centriaSQLConnection;
    ui->setupUi(this);

    ui->tableViewAttributes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewAttributes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewAttributes->setSelectionBehavior(QAbstractItemView::SelectRows);


    PopulateAttributesTable();
}

DialogAddAttribute::~DialogAddAttribute()
{
    delete ui;
}

void DialogAddAttribute::on_pushButtonCreateNewAttribute_clicked()
{
    if(_centriaSQLConnection != nullptr)
    {
        DialogCreateAttribute dialogCreateAttribute(_centriaSQLConnection, this);
        int result = dialogCreateAttribute.exec();
        if(result == QDialog::Accepted)
        {
            PopulateAttributesTable();
        }
    }
}

void DialogAddAttribute::PopulateAttributesTable()
{
    if(_objectTableModel != nullptr)
    {
        _objectTableModel->clear();
        delete _objectTableModel;

    }
    _objectTableModel = new QStandardItemModel(this);
    _objectTableModel->setColumnCount(3);
    _objectTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    _objectTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    _objectTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Value type"));

    if(_centriaSQLConnection != nullptr)
    {
        _sqlAttributes.clear();
        _sqlAttributes = _centriaSQLConnection->GetAttributes();
        _objectTableModel->setRowCount(_sqlAttributes.size());

        int rowIndex = 0;
        foreach(SQLAttribute sqlAttribute, _sqlAttributes)
        {
            _objectTableModel->setItem(rowIndex,0,new QStandardItem(QString::number(sqlAttribute.ID)));
            _objectTableModel->setItem(rowIndex,1,new QStandardItem(sqlAttribute.Name));
            _objectTableModel->setItem(rowIndex,2,new QStandardItem(sqlAttribute.ValueType));
            rowIndex++;
        }
    }
    ui->tableViewAttributes->setModel(_objectTableModel);

}

void DialogAddAttribute::on_buttonBox_accepted()
{

}

void DialogAddAttribute::on_tableViewAttributes_clicked(const QModelIndex &index)
{
    AddedSQLAttribute = nullptr;
    int row = _objectTableModel->itemFromIndex(index)->row();
    QStandardItem *idItem = _objectTableModel->item(row,0);
    quint64 id = idItem->text().toULongLong();
    if(id>0)
    {
        AddedSQLAttribute = &_sqlAttributes[id];
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(AddedSQLAttribute != nullptr);
}
