#include "mainwindow.h"
#include <QApplication>
#include <arduino_server_choice.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ArduinoServerChoice* arduinoServerChoice = new ArduinoServerChoice();

    if(arduinoServerChoice->exec() == QDialog::Rejected){
        a.quit();
        return Result::getLast()->getCode();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
