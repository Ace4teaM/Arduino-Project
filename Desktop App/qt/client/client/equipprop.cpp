#include "equipprop.h"
#include "ui_equipprop.h"

EquipProp::EquipProp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipProp)
{
    ui->setupUi(this);
}

EquipProp::~EquipProp()
{
    delete ui;
}
