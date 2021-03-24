#ifndef DIALOGCREATENEWOBJECT_H
#define DIALOGCREATENEWOBJECT_H

#include <QDialog>
#include <QUuid>

namespace Ui {
class DialogCreateNewObject;
}

class DialogCreateNewObject : public QDialog
{
    Q_OBJECT

public:
    QString Name = "";
    QUuid UUID;
    explicit DialogCreateNewObject(QWidget *parent = nullptr, QString name = "");
    ~DialogCreateNewObject();

private slots:
    void on_pushButtonCreateNewUUID_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogCreateNewObject *ui;
};

#endif // DIALOGCREATENEWOBJECT_H
