#include "newequipementdialog.h"
#include "ui_newequipementdialog.h"

NewEquipementDialog::NewEquipementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEquipementDialog)
{
    ui->setupUi(this);
}

NewEquipementDialog::~NewEquipementDialog()
{
    delete ui;
}
