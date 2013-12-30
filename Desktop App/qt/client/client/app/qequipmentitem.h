#ifndef QEQUIPEMENTITEM_H
#define QEQUIPEMENTITEM_H

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "../model/Equipment.h"

class QEquipmentItem : public QGraphicsRectItem
{
public:
    QEquipmentItem(const Equipment & equipment,QGraphicsItem* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Equipment & getEquipment();
protected:
    /*void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    bool sceneEvent(QEvent * event);*/
    void mousePressEvent( QGraphicsSceneMouseEvent *event );
signals:

public slots:
protected:
    Equipment equipment;
    QPixmap image;
    QMenu contextMenu;
};

#endif // QEQUIPEMENTITEM_H
