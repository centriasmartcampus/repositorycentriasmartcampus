#ifndef DIALOGCREATEATTRIBUTE_H
#define DIALOGCREATEATTRIBUTE_H

#include <QDialog>

#include "centriasqlconnection.h"

namespace Ui {
class DialogCreateAttribute;
}

class DialogCreateAttribute : public QDialog
{
    Q_OBJECT

public:
    SQLAttribute NewSQLAttribute;

    explicit DialogCreateAttribute(CentriaSQLConnection *centriaSQLConnection, QWidget *parent = nullptr);
    ~DialogCreateAttribute();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogCreateAttribute *ui;

    CentriaSQLConnection *_centriaSQLConnection = nullptr;
};

#endif // DIALOGCREATEATTRIBUTE_H
