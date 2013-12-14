#ifndef ARDUINO_SERVER_CHOICE_H
#define ARDUINO_SERVER_CHOICE_H

#include <QDialog>
#include "app/result.h"
#include "app/configurable.h"

namespace Ui {
    class ArduinoServerChoice;
}

class ArduinoServerChoice : public QDialog, public Configurable
{
    Q_OBJECT

public:
    explicit ArduinoServerChoice(QWidget *parent = 0);
    ~ArduinoServerChoice();

    //Configurable
    const QString getConfigTitle();
    const QString getConfigName();
    bool configUpdate(ConfigParamList& list);
    bool configRead(ConfigParamList& list);

private:
    Ui::ArduinoServerChoice *ui;
};

#endif // ARDUINO_SERVER_CHOICE_H
