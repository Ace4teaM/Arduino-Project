#ifndef QEQUIPEMENTITEM_H
#define QEQUIPEMENTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "../model/Equipement.h"

class QEquipementItem : public QGraphicsRectItem
{
public:
    QEquipementItem(const Equipement & equipement,QGraphicsItem* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:

public slots:
private:
    Equipement equipement;
    QPixmap image;
};

#endif // QEQUIPEMENTITEM_H
