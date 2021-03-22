#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidgetObjectHierarchy->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tableViewObject->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewObject->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewObject->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetAttributes->setContextMenuPolicy(Qt::CustomContextMenu);

    DTO = CentriaWebServiceDTO("CentriaWebService");
    if(DTO.CentriaFastCGITCPListener.size() > 0)
    {
        _centriaFastTCPListener = new CentriaFastCGITCPListener(DTO.CentriaFastCGITCPListener, this);
        connect(_centriaFastTCPListener, SIGNAL(NewRequest(CentriaFastCGIRequest&)),this, SLOT(NewRequest(CentriaFastCGIRequest&)));
    }

    if(DTO.CentriaSQLConnection.size() > 0)
    {
        _centriaSQLConnection = new CentriaSQLConnection(DTO.CentriaSQLConnection);
        PopulateTreeView();
        PopulateObjectList();
    }
}

MainWindow::~MainWindow()
{
    if(_centriaFastTCPListener != nullptr)
    {
        delete _centriaFastTCPListener;
    }

    if(_centriaSQLConnection != nullptr)
    {
        delete _centriaSQLConnection;
    }
    delete ui;
}

void MainWindow::NewRequest(CentriaFastCGIRequest &scFastCGIRequest)
{
    //scFastCGIRequest.Response.append("Testi\n\n\n");
    //scFastCGIRequest.Response.append("Mitä ihmettä <br> toinen rivi\n");
    //scFastCGIRequest.Response.append(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));

    scFastCGIRequest.Response.append("{\n");
    foreach(QString key, scFastCGIRequest.Parameters.keys())
    {
        scFastCGIRequest.Response.append(QString("\"%1\": \"%2\",\n").arg(key).arg(scFastCGIRequest.Parameters[key]));
    }
    scFastCGIRequest.Response.append(QString("\"Request\": "));
    scFastCGIRequest.Response.append(QString("\"%1\"\n").arg(QString(scFastCGIRequest.Request)));
    scFastCGIRequest.Response.append(QString("\"Content\": \"%1\"\n").arg(QString(scFastCGIRequest.Content)));
    scFastCGIRequest.Response.append("}\n");
}

void MainWindow::CreateNewHierarchyItem(QTreeWidgetItem* parentItem)
{
    DialogCreateHierarchyItem dialogCreateHierarchyItem(this);
    int result = dialogCreateHierarchyItem.exec();
    if(result == QDialog::Accepted)
    {
        if(_centriaSQLConnection != nullptr)
        {            
            SQLObjectHierarchy sqlObjectHierarchy;
            sqlObjectHierarchy.Name = dialogCreateHierarchyItem.Name;
            sqlObjectHierarchy.ParentID = parentItem != nullptr ? parentItem->text(1).toULongLong() : 0;
            _centriaSQLConnection->AddNewObjectHierarchy(sqlObjectHierarchy);
            PopulateTreeView();
        }
    }
}

void MainWindow::DeleteHierarchyItem(QTreeWidgetItem *item)
{
    if(_centriaSQLConnection != nullptr)
    {
        quint64 ID = item != nullptr ? item->text(1).toULongLong() : 0;
        _centriaSQLConnection->DeleteObjectHierarchy(ID);
        PopulateTreeView();
    }
}

void MainWindow::AddNewAttribute()
{
    if(_centriaSQLConnection != nullptr)
    {
        DialogAddAttribute dialogAddAttribute(_centriaSQLConnection, this);
        int result = dialogAddAttribute.exec();
        if(result == QDialog::Accepted)
        {
            SQLAttribute *addedSQLAttribute = dialogAddAttribute.AddedSQLAttribute;
            if(addedSQLAttribute != nullptr && _selectedSQLObjectHierarchy != nullptr)
            {
                SQLAttributeValue sqlAttributeValue;
                sqlAttributeValue.AttributeID = addedSQLAttribute->ID;
                sqlAttributeValue.ObjectUUID = _selectedSQLObjectHierarchy->ObjectUUID;
                sqlAttributeValue.Value = QByteArray();
                _centriaSQLConnection->AddNewAttributeValue(sqlAttributeValue);
                PopulateObjectAttributesTable();
            }
        }
    }
}

void MainWindow::RemoveAttribute(QTableWidgetItem *item)
{

}

void MainWindow::PopulateTreeView()
{
    ui->treeWidgetObjectHierarchy->clear();
    if(_centriaSQLConnection != nullptr)
    {
        _sqlObjectHierarchies.clear();
        _sqlObjectHierarchies = _centriaSQLConnection->GetObjectHierarchies();

        QMap<quint64, QTreeWidgetItem*> items;
        foreach(SQLObjectHierarchy sqlObjectHierarchy, _sqlObjectHierarchies)
        {
            if(sqlObjectHierarchy.ParentID == 0)
            {
                QTreeWidgetItem *rootItem = new QTreeWidgetItem();
                rootItem->setText(0, sqlObjectHierarchy.Name);
                rootItem->setText(1, QString::number(sqlObjectHierarchy.ID));
                ui->treeWidgetObjectHierarchy->addTopLevelItem(rootItem);
                items.insert(sqlObjectHierarchy.ID,rootItem);
            }
            else
            {
                QTreeWidgetItem *parentItem = items[sqlObjectHierarchy.ParentID];
                if(parentItem != nullptr)
                {
                    QTreeWidgetItem *childItem = new QTreeWidgetItem();
                    childItem->setText(0, sqlObjectHierarchy.Name);
                    childItem->setText(1, QString::number(sqlObjectHierarchy.ID));
                    parentItem->addChild(childItem);
                    items.insert(sqlObjectHierarchy.ID,childItem);
                }
            }
        }
    }
}

void MainWindow::PopulateObjectList()
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

void MainWindow::PopulateObjectAttributesTable()
{
    if(_centriaSQLConnection != nullptr && _selectedSQLObjectHierarchy != nullptr)
    {
        QMap<quint64, SQLAttributeValue> sqlAttributeValues = _centriaSQLConnection->GetObjectAttributeValues(_selectedSQLObjectHierarchy->ObjectUUID);
        QMap<quint64, SQLAttribute> sqlAttributes = _centriaSQLConnection->GetAttributes();

        if(_attributeTableModel != nullptr)
        {
            _attributeTableModel->clear();
            delete _attributeTableModel;

        }
        _attributeTableModel = new QStandardItemModel(this);
        _attributeTableModel->setColumnCount(2);
        _attributeTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        _attributeTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("UUID"));

        if(_centriaSQLConnection != nullptr)
        {
            _attributeTableModel->setRowCount(sqlAttributeValues.size());

            int rowIndex = 0;
            foreach(SQLAttributeValue sqlAttributeValue, sqlAttributeValues)
            {
                SQLAttribute sqlAttribute = sqlAttributes[sqlAttributeValue.AttributeID];

                _attributeTableModel->setItem(rowIndex,0,new QStandardItem(sqlAttribute.Name));
                _attributeTableModel->setItem(rowIndex,1,new QStandardItem(QString(sqlAttributeValue.Value)));
                rowIndex++;
            }


        }
        ui->tableViewObject->setModel(_attributeTableModel);
    }
}

//bool MainWindow::eventFilter(QObject *target, QEvent *event)
//{
//    if (target == ui->treeViewObject)
//    {
//        QContextMenuEvent* m = dynamic_cast<QContextMenuEvent*>(event);
//        if (event->type() == QEvent::ContextMenu)
//        {
//           QMenu contextMenu(tr("Context menu"), this);

//           QAction actionCreateNewObject("Create New Object", this);
//           connect(&actionCreateNewObject, SIGNAL(triggered()), this, SLOT(CreateNewObject()));
//           contextMenu.addAction(&actionCreateNewObject);

//           contextMenu.exec(mapToGlobal(m->pos()));
//            return true;
//        }
//    }
//    return false;

//}




void MainWindow::on_treeWidgetObjectHierarchy_itemChanged(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_treeWidgetObjectHierarchy_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *parentItem = ui->treeWidgetObjectHierarchy->itemAt(pos);

    QString command = "";
    if(parentItem == nullptr)
    {
        QMenu menu(this);
        QAction actionCreateNewHierarchyItem("Create new root item", this);
        actionCreateNewHierarchyItem.setProperty("Command", "AddRootItem");
        menu.addAction(&actionCreateNewHierarchyItem);
        //menu.exec( ui->treeWidgetObjectHierarchy->mapToGlobal(pos));

        QAction *selectedAction = menu.exec( ui->treeWidgetObjectHierarchy->mapToGlobal(pos));
        command = selectedAction != nullptr ? selectedAction->property("Command").toString() : "";
    }
    else
    {
        QMenu menu(this);
        QAction actionAddNewChildItem(QString("Create new child item for %1").arg(parentItem->text(0)), this);
        actionAddNewChildItem.setProperty("Command", "AddChildItem");
        menu.addAction(&actionAddNewChildItem);

        QAction actionDeleteItem(QString("Delete %1 item").arg(parentItem->text(0)), this);
        actionDeleteItem.setProperty("Command", "DeleteItem");
        menu.addAction(&actionDeleteItem);

        QAction *selectedAction = menu.exec( ui->treeWidgetObjectHierarchy->mapToGlobal(pos));
        command = selectedAction != nullptr ? selectedAction->property("Command").toString() : "";
    }

    if(command == "AddRootItem")
    {
        CreateNewHierarchyItem(nullptr);
    }
    else if(command == "AddChildItem")
    {
        CreateNewHierarchyItem(parentItem);
    }
    else if(command == "DeleteItem")
    {
        DeleteHierarchyItem(parentItem);
    }
}

void MainWindow::on_treeWidgetObjectHierarchy_itemClicked(QTreeWidgetItem *item, int column)
{
    _selectedSQLObjectHierarchy = nullptr;
    quint64 ID = item != nullptr ? item->text(1).toULongLong() : 0;
    if(ID > 0)
    {
        _selectedSQLObjectHierarchy = &_sqlObjectHierarchies[ID];
        ui->lineEditObjectHierarchyName->setText(_selectedSQLObjectHierarchy->Name);

        bool objectLinkExists = !_selectedSQLObjectHierarchy->ObjectUUID.isNull();
        ui->groupBoxObject->setEnabled(objectLinkExists);
        ui->pushButtonCreateObjectLink->setEnabled(!objectLinkExists);
        ui->tableWidgetAttributes->setEnabled(objectLinkExists);
        if(objectLinkExists)
        {
            SQLObject sqlObject = _sqlObjects[_selectedSQLObjectHierarchy->ObjectUUID];
            ui->lineEditObjecName->setText(sqlObject.Name);
            ui->lineEditObjecUUID->setText(sqlObject.ObjectUUID.toString(QUuid::WithoutBraces));            
        }
        else
        {
            ui->lineEditObjecName->setText("");
            ui->lineEditObjecUUID->setText("");
        }

    }
    PopulateObjectAttributesTable();
}

void MainWindow::on_pushButtonCreateObjectLink_clicked()
{
    QTreeWidgetItem* item = ui->treeWidgetObjectHierarchy->selectedItems().first();
    quint64 ID = item != nullptr ? item->text(1).toULongLong() : 0;
    if(ID > 0)
    {
        SQLObjectHierarchy sqlObjectHierarchy = _sqlObjectHierarchies[ID];

        if(_centriaSQLConnection != nullptr)
        {
            DialogCreateObjectLink dialogCreateObjectLink(_centriaSQLConnection, sqlObjectHierarchy, this);
            int result = dialogCreateObjectLink.exec();
            if(result == QDialog::Accepted)
            {
                sqlObjectHierarchy.ObjectUUID = dialogCreateObjectLink.SelectedSQLObject->ObjectUUID;
                _centriaSQLConnection->UpdateObjectHierarchy(sqlObjectHierarchy);
                PopulateTreeView();
            }
        }
    }
}

void MainWindow::on_pushButtonCreateNewObject_clicked()
{
    if(_centriaSQLConnection != nullptr)
    {
        DialogCreateNewObject dialogCreateNewObject(this);
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

void MainWindow::on_tableWidgetAttributes_customContextMenuRequested(const QPoint &pos)
{

    QTableWidgetItem *parentItem = ui->tableWidgetAttributes->itemAt(pos);

    QMenu menu(this);
    QAction actionAddNewAttribute("Add new attribute", this);
    actionAddNewAttribute.setProperty("Command", "AddNewAttribute");
    menu.addAction(&actionAddNewAttribute);

    if(parentItem != nullptr)
    {
        QAction actionRemoveAttribute(QString("Delete %1 attribute").arg(parentItem->text()), this);
        actionRemoveAttribute.setProperty("Command", "RemoveAttribute");
        menu.addAction(&actionRemoveAttribute);
    }

    QAction *selectedAction = menu.exec( ui->tableWidgetAttributes->mapToGlobal(pos));
    QString command = selectedAction != nullptr ? selectedAction->property("Command").toString() : "";


    if(command == "AddNewAttribute")
    {
        AddNewAttribute();
    }
    else if(command == "RemoveAttribute")
    {
        RemoveAttribute(parentItem);
    }
}
