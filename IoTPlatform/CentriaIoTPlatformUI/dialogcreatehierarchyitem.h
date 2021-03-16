#ifndef DIALOGCREATEHIERARCHYITEM_H
#define DIALOGCREATEHIERARCHYITEM_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DialogCreateHierarchyItem;
}

class DialogCreateHierarchyItem : public QDialog
{
    Q_OBJECT

public:
    QString Name = "";
    explicit DialogCreateHierarchyItem(QWidget *parent = nullptr);
    ~DialogCreateHierarchyItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogCreateHierarchyItem *ui;
};

#endif // DIALOGCREATEHIERARCHYITEM_H
