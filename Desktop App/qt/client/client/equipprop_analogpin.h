#ifndef EQUIPPROP_ANALOGPIN_H
#define EQUIPPROP_ANALOGPIN_H

#include <QWidget>

namespace Ui {
class EquipProp_AnalogPin;
}

class EquipProp_AnalogPin : public QWidget
{
    Q_OBJECT

public:
    explicit EquipProp_AnalogPin(QWidget *parent = 0);
    ~EquipProp_AnalogPin();

private:
    Ui::EquipProp_AnalogPin *ui;
};

#endif // EQUIPPROP_ANALOGPIN_H
