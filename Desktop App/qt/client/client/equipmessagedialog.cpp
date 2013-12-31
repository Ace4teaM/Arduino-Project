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
    app->com.begin();
    app->com.makeText(this->ui->plainTextEdit->toPlainText().toLatin1());
    QHostAddress host("127.0.0.1");
    app->com.send(host);
    //app->com.send(equipment->server->ip);
}
