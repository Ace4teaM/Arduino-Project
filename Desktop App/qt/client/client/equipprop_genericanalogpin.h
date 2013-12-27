#ifndef EQUIPPROP_GENERICANALOGPIN_H
#define EQUIPPROP_GENERICANALOGPIN_H

#include <QWidget>

namespace Ui {
class NewEquipProp_GenericAnalogPin;
}

class EquipProp_GenericAnalogPin : public QWidget
{
    Q_OBJECT
public:
    explicit EquipProp_GenericAnalogPin(QWidget *parent = 0);
    ~EquipProp_GenericAnalogPin();

signals:

public slots:

private:
    Ui::NewEquipProp_GenericAnalogPin *ui;
};

#endif // EQUIPPROP_GENERICANALOGPIN_H
