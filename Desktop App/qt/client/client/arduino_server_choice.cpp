#include "arduino_server_choice.h"
#include "ui_arduino_server_choice.h"

ArduinoServerChoice::ArduinoServerChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArduinoServerChoice)
{
    ui->setupUi(this);
}

ArduinoServerChoice::~ArduinoServerChoice()
{
    delete ui;
}

/*---------------------------------------------------------------------------
    Configuration
---------------------------------------------------------------------------*/

const QString ArduinoServerChoice::getConfigTitle(){
    return "Choix serveur Arduino";
}

const QString ArduinoServerChoice::getConfigName(){
    return "arduino_server";
}

bool ArduinoServerChoice::configUpdate(ConfigParamList& list){

    Configurable::configToWidget(this,list);

    return RESULT_OK;
}

bool ArduinoServerChoice::configRead(ConfigParamList& list){

    Configurable::configFromWidget(this,list);

    return RESULT_OK;
}
