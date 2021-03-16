#ifndef DIALOGCREATEOBJECTLINK_H
#define DIALOGCREATEOBJECTLINK_H

#include <QDialog>
#include <QPushButton>
#include <QStandardItemModel>

#include "Entities/sqlobject.h"
#include "Entities/sqlobjecthierarchy.h"
#include "centriasqlconnection.h"

namespace Ui {
class DialogCreateObjectLink;
}

class DialogCreateObjectLink : public QDialog
{
    Q_OBJECT

public:
    SQLObject *SelectedSQLObject = nullptr;

    explicit DialogCreateObjectLink(CentriaSQLConnection *centriaSQLConnection, SQLObjectHierarchy sqlObjectHierarchy, QWidget *parent = nullptr);
    ~DialogCreateObjectLink();

private slots:


    void on_tableViewObject_clicked(const QModelIndex &index);

private:
    Ui::DialogCreateObjectLink *ui;
    QStandardItemModel *_objectTableModel = nullptr;

    CentriaSQLConnection *_centriaSQLConnection = nullptr;
    SQLObjectHierarchy _sqlObjectHierarchy;
    QMap<QUuid, SQLObject> _sqlObjects;


    void PopulateObjectList();
};

#endif // DIALOGCREATEOBJECTLINK_H
