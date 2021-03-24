#include "dialogcreateobjectlink.h"
#include "ui_dialogcreateobjectlink.h"

DialogCreateObjectLink::DialogCreateObjectLink(CentriaSQLConnection *centriaSQLConnection, SQLObjectHierarchy sqlObjectHierarchy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateObjectLink)
{
    _centriaSQLConnection = centriaSQLConnection;
    _sqlObjectHierarchy = sqlObjectHierarchy;
    ui->setupUi(this);

    this->setWindowTitle("Crete new link between object and hierarchy");
    ui->labelObjectHierarchyName->setText(_sqlObjectHierarchy.Name);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Create Link");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->tableViewObject->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewObject->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewObject->setSelectionBehavior(QAbstractItemView::SelectRows);
    PopulateObjectList();
}


DialogCreateObjectLink::~DialogCreateObjectLink()
{
    delete ui;
}

void DialogCreateObjectLink::PopulateObjectList()
{
    if(_objectTableModel != nullptr)
    {
        _objectTableModel->clear();
        delete _objectTableModel;

    }
    _objectTableModel = new QStandardItemModel(this);
    _objectTableModel->setColumnCount(2);
    _objectTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    _objectTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("UUID"));

    if(_centriaSQLConnection != nullptr)
    {
        _sqlObjects.clear();
        _sqlObjects = _centriaSQLConnection->GetObjects();
        _objectTableModel->setRowCount(_sqlObjects.size());

        int rowIndex = 0;
        foreach(SQLObject sqlObject, _sqlObjects)
        {

            _objectTableModel->setItem(rowIndex,0,new QStandardItem(sqlObject.Name));
            _objectTableModel->setItem(rowIndex,1,new QStandardItem(sqlObject.ObjectUUID.toString()));
            rowIndex++;
        }


    }
    ui->tableViewObject->setModel(_objectTableModel);
}


void DialogCreateObjectLink::on_tableViewObject_clicked(const QModelIndex &index)
{
    SelectedSQLObject = nullptr;
    int row = _objectTableModel->itemFromIndex(index)->row();
    QStandardItem *uuidItem = _objectTableModel->item(row,1);
    QUuid objectUUID = QUuid::fromString(uuidItem->text());
    if(!objectUUID.isNull())
    {
        SelectedSQLObject = &_sqlObjects[objectUUID];
    }


    if(SelectedSQLObject != nullptr)
    {
        ui->labelSelectedObject->setText(QString("Selected: %1 %2").arg(SelectedSQLObject->Name).arg(SelectedSQLObject->ObjectUUID.toString()));
    }
    else
    {
        ui->labelSelectedObject->setText("");
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(SelectedSQLObject != nullptr);
}

void DialogCreateObjectLink::on_pushButtonCreateNewObject_clicked()
{
    if(_centriaSQLConnection != nullptr)
    {
        DialogCreateNewObject dialogCreateNewObject(this, _sqlObjectHierarchy.Name);
        int result = dialogCreateNewObject.exec();
        if(result == QDialog::Accepted)
        {
            SQLObject sqlObject;
            sqlObject.Name = dialogCreateNewObject.Name;
            sqlObject.ObjectUUID = dialogCreateNewObject.UUID;

            if(!sqlObject.ObjectUUID.isNull() && sqlObject.Name.size() > 0)
            {
                _centriaSQLConnection->AddNewObject(sqlObject);
                PopulateObjectList();
            }
        }
    }
}
