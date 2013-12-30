#include "equipprop_analogpin.h"
#include "ui_equipprop_analogpin.h"

EquipProp_AnalogPin::EquipProp_AnalogPin(Equipment & equip,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipProp_AnalogPin)
{
    ui->setupUi(this);

    ui->lineEdit_Pin->setText("0");
    ui->horizontalSlider_Intensity->setMinimum(0);
    ui->horizontalSlider_Intensity->setMaximum(255);
}

EquipProp_AnalogPin::~EquipProp_AnalogPin()
{
    delete ui;
}

void EquipProp_AnalogPin::applyProp(Equipment & equip)
{
}
