#ifndef EQUIPPROP_ANALOGPIN_H
#define EQUIPPROP_ANALOGPIN_H

#include <QWidget>
#include "iequipprop.h"
#include "model/Equipment.h"

namespace Ui {
class EquipProp_AnalogPin;
}

class EquipProp_AnalogPin : public QWidget, public IEquipProp
{
    Q_OBJECT

public:
    explicit EquipProp_AnalogPin(Equipment & equip,QWidget *parent = 0);
    ~EquipProp_AnalogPin();
    void applyProp(Equipment & equip);

private:
    Ui::EquipProp_AnalogPin *ui;
};

#endif // EQUIPPROP_ANALOGPIN_H
