#include "equipprop_digitalpin.h"
#include "ui_equipprop_digitalpin.h"

EquipProp_DigitalPin::EquipProp_DigitalPin(Equipment & equip,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipProp_DigitalPin)
{
    ui->setupUi(this);
}

EquipProp_DigitalPin::~EquipProp_DigitalPin()
{
    delete ui;
}


void EquipProp_DigitalPin::applyProp(Equipment & equip)
{
}
