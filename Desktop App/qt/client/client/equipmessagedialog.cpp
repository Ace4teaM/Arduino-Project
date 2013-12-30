#include "equipmessagedialog.h"
#include "ui_equipmessagedialog.h"

EquipMessageDialog::EquipMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipMessageDialog)
{
    ui->setupUi(this);
}

EquipMessageDialog::~EquipMessageDialog()
{
    delete ui;
}
