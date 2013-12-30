#include "equipprop.h"
#include "ui_equipprop.h"

EquipProp::EquipProp(Equipment & equip,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipProp)
{
    ui->setupUi(this);

    ui->label_id->setText(QString("%1").arg(equip.equipmentId));
    ui->label_type->setText(equip.type);
    ui->lineEdit_name->setText(equip.name);
}

EquipProp::~EquipProp()
{
    delete ui;
}

void EquipProp::applyProp(Equipment & equip)
{
    equip.name = ui->lineEdit_name->text();
}
