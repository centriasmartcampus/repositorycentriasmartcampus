#ifndef DIALOGADDATTRIBUTE_H
#define DIALOGADDATTRIBUTE_H

#include <QDialog>
#include <QStandardItemModel>

#include "centriasqlconnection.h"
#include "dialogcreateattribute.h"

namespace Ui {
class DialogAddAttribute;
}

class DialogAddAttribute : public QDialog
{
    Q_OBJECT

public:
    SQLAttribute *AddedSQLAttribute = nullptr;

    explicit DialogAddAttribute(CentriaSQLConnection *centriaSQLConnection, QWidget *parent = nullptr);
    ~DialogAddAttribute();

private slots:
    void on_pushButtonCreateNewAttribute_clicked();

    void on_buttonBox_accepted();

    void on_tableViewAttributes_clicked(const QModelIndex &index);

private:
    Ui::DialogAddAttribute *ui;

    CentriaSQLConnection *_centriaSQLConnection = nullptr;
    QStandardItemModel *_objectTableModel = nullptr;
    QMap<quint64, SQLAttribute> _sqlAttributes;

    void PopulateAttributesTable();
};

#endif // DIALOGADDATTRIBUTE_H
