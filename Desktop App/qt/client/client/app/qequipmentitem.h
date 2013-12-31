#ifndef QEQUIPEMENTITEM_H
#define QEQUIPEMENTITEM_H

#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include "../model/Equipment.h"
#include "qserveritem.h"
#include "qequipmentscene.h"

class QEquipmentItem : public QGraphicsRectItem
{
public:
    QEquipmentItem(const Equipment & equipment,QGraphicsItem* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Equipment & getEquipment();
    QServerItem * getServerItem( );
protected:
signals:

protected:
    Equipment equipment;
    QPixmap image;
};

#endif // QEQUIPEMENTITEM_H
