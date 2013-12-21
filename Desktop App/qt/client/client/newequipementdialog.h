#ifndef NEWEQUIPEMENTDIALOG_H
#define NEWEQUIPEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class NewEquipementDialog;
}

class NewEquipementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEquipementDialog(QWidget *parent = 0);
    ~NewEquipementDialog();

private:
    Ui::NewEquipementDialog *ui;
};

#endif // NEWEQUIPEMENTDIALOG_H
