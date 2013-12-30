#ifndef EQUIPPROP_DIGITALPIN_H
#define EQUIPPROP_DIGITALPIN_H

#include <QWidget>
#include "iequipprop.h"
#include "model/Equipment.h"

namespace Ui {
class EquipProp_DigitalPin;
}

class EquipProp_DigitalPin : public QWidget, public IEquipProp
{
    Q_OBJECT

public:
    explicit EquipProp_DigitalPin(Equipment & equip,QWidget *parent = 0);
    ~EquipProp_DigitalPin();
    void applyProp(Equipment & equip);

private:
    Ui::EquipProp_DigitalPin *ui;
};

#endif // EQUIPPROP_DIGITALPIN_H
