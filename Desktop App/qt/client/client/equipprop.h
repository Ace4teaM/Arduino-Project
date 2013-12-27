#ifndef EQUIPPROP_H
#define EQUIPPROP_H

#include <QWidget>

namespace Ui {
class EquipProp;
}

class EquipProp : public QWidget
{
    Q_OBJECT

public:
    explicit EquipProp(QWidget *parent = 0);
    ~EquipProp();

private:
    Ui::EquipProp *ui;
};

#endif // EQUIPPROP_H
