#include "equipprop_genericanalogpin.h"
#include "ui_equipprop_genericanalogpin.h"

EquipProp_GenericAnalogPin::EquipProp_GenericAnalogPin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewEquipProp_GenericAnalogPin)
{
    ui->lineEdit_PIN->setTex("ok");
}
