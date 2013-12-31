#ifndef QSERVERITEM_H
#define QSERVERITEM_H

#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "../model/Server.h"

class QServerItem : public QGraphicsRectItem
{
public:
    QServerItem(const Server & equipment,QGraphicsItem* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Server & getServer();
protected:
signals:

public slots:
protected:
    Server server;
    QPixmap image;
};

#endif // QSERVERITEM_H
