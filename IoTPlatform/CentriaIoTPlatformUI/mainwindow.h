#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QMenu>
#include <QTreeWidgetItem>
#include <QRadioButton>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStandardItemModel>

#include "dialogcreatehierarchyitem.h"
#include "dialogcreateobjectlink.h"
#include "dialogcreatenewobject.h"
#include "dialogaddattribute.h"

#include "DTO/centriawebservicedto.h"
#include "../Common/centriafastcgitcplistener.h"
#include "centriasqlconnection.h"
#include "Entities/sqlattributevalue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CentriaWebServiceDTO DTO;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void NewRequest(CentriaFastCGIRequest& scFastCGIRequest);


private slots:
    void on_treeWidgetObjectHierarchy_itemChanged(QTreeWidgetItem *item, int column);
    void on_treeWidgetObjectHierarchy_customContextMenuRequested(const QPoint &pos);
    void on_treeWidgetObjectHierarchy_itemClicked(QTreeWidgetItem *item, int column);
    void on_pushButtonCreateObjectLink_clicked();
    void on_pushButtonCreateNewObject_clicked();    
    void on_tableWidgetAttributes_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

     CentriaFastCGITCPListener *_centriaFastTCPListener = nullptr;
     CentriaSQLConnection *_centriaSQLConnection = nullptr;

     QMap<quint64, SQLObjectHierarchy> _sqlObjectHierarchies;
     QMap<QUuid, SQLObject> _sqlObjects;

     SQLObjectHierarchy *_selectedSQLObjectHierarchy = nullptr;

     QStandardItemModel *_objectTableModel = nullptr;
     QStandardItemModel *_attributeTableModel = nullptr;

     void PopulateTreeView();
     void PopulateObjectList();
     void PopulateObjectAttributesTable();
     void CreateNewHierarchyItem(QTreeWidgetItem* parentItem = nullptr);
     void DeleteHierarchyItem(QTreeWidgetItem* item);

     void AddNewAttribute();
     void RemoveAttribute(QTableWidgetItem* item);


     //bool eventFilter(QObject *obj, QEvent *e);
};

#endif // MAINWINDOW_H
