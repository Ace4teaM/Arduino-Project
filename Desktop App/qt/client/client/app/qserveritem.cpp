#include "qserveritem.h"

QServerItem::QServerItem(const Server & server,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    this->image = QPixmap(":/equipement/circuit");
    this->server = server;
}

void QServerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter,option,widget);

    //image
    if(!image.isNull())
        painter->drawPixmap(this->boundingRect().toRect(),image);

    //name
    QPen pen(QColor("#000000"), 2.0, Qt::DotLine, Qt::FlatCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    painter->drawText(this->boundingRect(),this->server.ip,QTextOption(Qt::AlignCenter));
    pen.setColor(QColor("#ffffff"));
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    QRectF rect=this->boundingRect();
    rect.adjust(1,1,1,1);
    painter->drawText(rect,this->server.name,QTextOption(Qt::AlignCenter));
}

Server & QServerItem::getServer()
{
    return this->server;
}
