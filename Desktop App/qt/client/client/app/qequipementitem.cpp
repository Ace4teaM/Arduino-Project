#include "qequipementitem.h"

QEquipementItem::QEquipementItem(const Equipement & equipement,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    this->image = QPixmap(":/equipement/"+equipement.type);
    this->equipement = equipement;
}

void QEquipementItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter,option,widget);

    //image
    if(!image.isNull())
        painter->drawPixmap(this->boundingRect().toRect(),image);

    //name
    QPen pen(QColor("#000000"), 2.0, Qt::DotLine, Qt::FlatCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    painter->drawText(this->boundingRect(),this->equipement.name,QTextOption(Qt::AlignCenter));
    pen.setColor(QColor("#ffffff"));
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 8, QFont::Bold));
    QRectF rect=this->boundingRect();
    rect.adjust(1,1,1,1);
    painter->drawText(rect,this->equipement.name,QTextOption(Qt::AlignCenter));

}

Equipement & QEquipementItem::getEquipement()
{
    return this->equipement;
}
