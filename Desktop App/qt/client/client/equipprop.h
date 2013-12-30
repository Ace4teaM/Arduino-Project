#ifndef EQUIPPROP_H
#define EQUIPPROP_H

#include <QWidget>
#include "iequipprop.h"
#include "model/Equipment.h"

namespace Ui {
class EquipProp;
}

class EquipProp : public QWidget, public IEquipProp
{
    Q_OBJECT

public:
    explicit EquipProp(Equipment & equip,QWidget *parent = 0);
    ~EquipProp();
    void applyProp(Equipment & equip);

private:
    Ui::EquipProp *ui;
};

#endif // EQUIPPROP_H
