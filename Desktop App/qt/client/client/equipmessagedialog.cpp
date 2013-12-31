#include "equipmessagedialog.h"
#include "ui_equipmessagedialog.h"

EquipMessageDialog::EquipMessageDialog(Equipment & equipment,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipMessageDialog)
{
    this->equipment = &equipment;
    ui->setupUi(this);
}

EquipMessageDialog::~EquipMessageDialog()
{
    delete ui;
}

void EquipMessageDialog::on_buttonBox_accepted()
{
    qDebug() << "on_buttonBox_accepted";
    if(!app->com.begin())
        return;
    app->com.makeText(this->ui->plainTextEdit->toPlainText().toLatin1());
    QHostAddress host("192.168.1.29");
    app->com.end();
    app->com.send(host);
    //app->com.send(equipment->server->ip);
}
