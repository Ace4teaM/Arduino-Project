#include "qequipmentitem.h"

QEquipmentItem::QEquipmentItem(const Equipment & equipment,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    this->image = QPixmap(":/equipement/"+equipment.type);
    this->equipment = equipment;


    //initilise le menu contextuel
    contextMenu.addAction("Envoyer un message...");
}

void QEquipmentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter,option,widget);

    //image
    if(!image.isNull())
        painter->drawPixmap(this->boundingRect().toRect(),image);

    //name
    QPen pen(QColor("#000000"), 2.0, Qt::DotLine, Qt::FlatCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    painter->drawText(this->boundingRect(),this->equipment.name,QTextOption(Qt::AlignCenter));
    pen.setColor(QColor("#ffffff"));
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    QRectF rect=this->boundingRect();
    rect.adjust(1,1,1,1);
    painter->drawText(rect,this->equipment.name,QTextOption(Qt::AlignCenter));
}

Equipment & QEquipmentItem::getEquipment()
{
    return this->equipment;
}

/* NOT WORK
bool QEquipmentItem::sceneEvent(QEvent * event)
{
    qDebug() << "sceneEvent" << event->type();
    QGraphicsItem::sceneEvent(event);
}
void QEquipmentItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    qDebug() << "contextMenuEvent";
    QMenu menu;
    menu.addAction("Remove");
    menu.addAction("Mark");
    menu.exec(event->screenPos());
    event->accept();
}*/

void QEquipmentItem::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    if(event->button() == Qt::RightButton)
    {
        contextMenu.exec(event->screenPos());
        event->accept();
    }
    QGraphicsItem::mousePressEvent(event);
}
