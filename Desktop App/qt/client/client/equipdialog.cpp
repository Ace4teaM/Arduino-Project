#include "equipdialog.h"
#include "ui_equipdialog.h"

EquipDialog::EquipDialog(Equipment & equip,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipDialog)
{
    m_equip=&equip;
    ui->setupUi(this);
    ui->verticalLayout_prop->addWidget(new EquipProp(equip,this));
    ui->verticalLayout_prop->addWidget(new EquipProp_AnalogPin(equip,this));
}

EquipDialog::~EquipDialog()
{
    delete ui;
}

void EquipDialog::on_buttonBox_accepted()
{
    QList<QWidget*> list = this->findChildren<QWidget*>();
    qDebug() << "list=" << list.count();
    for(int i=0; i<list.count(); i++){
        QWidget* obj = list.at(i);
        IEquipProp* propDialog = dynamic_cast<IEquipProp*>(obj);
        if(propDialog)
            propDialog->applyProp(*m_equip);
    }
}
