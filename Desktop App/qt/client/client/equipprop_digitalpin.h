#ifndef EQUIPPROP_DIGITALPIN_H
#define EQUIPPROP_DIGITALPIN_H

#include <QWidget>

namespace Ui {
class EquipProp_DigitalPin;
}

class EquipProp_DigitalPin : public QWidget
{
    Q_OBJECT

public:
    explicit EquipProp_DigitalPin(QWidget *parent = 0);
    ~EquipProp_DigitalPin();

private:
    Ui::EquipProp_DigitalPin *ui;
};

#endif // EQUIPPROP_DIGITALPIN_H
