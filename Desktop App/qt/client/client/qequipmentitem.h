#ifndef QEQUIPEMENTITEM_H
#define QEQUIPEMENTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "../model/Equipment.h"

class QEquipmentItem : public QGraphicsRectItem
{
public:
    QEquipmentItem(const Equipment & equipment,QGraphicsItem* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Equipment & getEquipment();
signals:

public slots:
protected:
    Equipment equipment;
    QPixmap image;
};

#endif // QEQUIPEMENTITEM_H
