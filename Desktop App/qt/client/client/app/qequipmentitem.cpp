#include "qequipmentitem.h"

/**
 * @brief Constructeur
 * @param equipment Instance de l'équipement
 * @param parent Parent du widget
 */
QEquipmentItem::QEquipmentItem(const Equipment & equipment,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    this->image = QPixmap(":/equipement/"+equipment.type);
    this->equipment = equipment;
}

/**
 * @brief Retourne le model de données
 * @return Equipment
 */
Equipment & QEquipmentItem::getEquipment()
{
    return this->equipment;
}

/**
 * @brief Obtient l'item du serveur associé
 * @return Serveur
*/
QServerItem * QEquipmentItem::getServerItem( ) {
    if(this->equipment.server == NULL)
        return NULL;
    QList<QWidget*> list = this->scene()->findChildren<QWidget*>();
    for(int i=0; i<list.count(); i++){
        QServerItem* item = dynamic_cast<QServerItem*>(list.at(i));
        if(item && item->getServer().serverId == this->equipment.server->serverId)
            qDebug() << "serverId=" << item->getServer().serverId;
    }
}


/*-------------------------------------------------------------------------------
 * EVENEMENTS
 * ------------------------------------------------------------------------------*/

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
