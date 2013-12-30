#ifndef EQUIPDIALOG_H
#define EQUIPDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include "equipprop.h"
#include "equipprop_analogpin.h"
#include "model/Equipment.h"

namespace Ui {
class EquipDialog;
}

class EquipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipDialog(Equipment & equip,QWidget *parent = 0);
    ~EquipDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EquipDialog *ui;
    Equipment * m_equip;
};

#endif // EQUIPDIALOG_H
