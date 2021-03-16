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

//#include "dialogcreateobject.h"
#include "dialogcreatehierarchyitem.h"
#include "dialogcreateobjectlink.h"

#include "DTO/centriawebservicedto.h"
#include "../Common/centriafastcgitcplistener.h"
#include "centriasqlconnection.h"

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

private:
    Ui::MainWindow *ui;

     CentriaFastCGITCPListener *_centriaFastTCPListener = nullptr;
     CentriaSQLConnection *_centriaSQLConnection = nullptr;

     QMap<quint64, SQLObjectHierarchy> _sqlObjectHierarchies;
     QMap<QUuid, SQLObject> _sqlObjects;

     QStandardItemModel *_objectTableModel = nullptr;

     void PopulateTreeView();
     void PopulateObjectList();
     void CreateNewHierarchyItem(QTreeWidgetItem* parentItem = nullptr);
     void DeleteHierarchyItem(QTreeWidgetItem* item);


     //bool eventFilter(QObject *obj, QEvent *e);
};

#endif // MAINWINDOW_H
