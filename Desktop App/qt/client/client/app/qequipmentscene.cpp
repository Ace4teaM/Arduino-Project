#include "qequipmentscene.h"

QEquipmentScene::QEquipmentScene()
{
}

/*
 * Affiche le dialogue de propriétés sur l'équipement
*/
void QEquipmentScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent){
    qDebug() << QString("mouseDoubleClickEvent");
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

    //récupére les infos sur l'équipement
    QEquipmentItem* item = dynamic_cast<QEquipmentItem*>(this->selectedItems().at(0));
    if(!item) return;

    qDebug() << item->getEquipment().name;

    // initialise le dialogue de proprietes
    EquipDialog *dialog = new EquipDialog(item->getEquipment());
    dialog->exec();
}

/*
 * Affiche le menu contextuel de l'équipement

void QEquipmentScene::contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent){
    qDebug() << "contextMenuEvent";
    QMenu *menu = new QMenu();
    menu->addAction("Action 1");
    menu->addAction("Action 2");
    menu->popup(contextMenuEvent->screenPos());

    connect(menu, SIGNAL(triggered(QAction *)),this, SLOT(contextMenuTriggered(QAction *)));
    contextMenuEvent->accept();
}

void QEquipmentScene::contextMenuTriggered(QAction * action){
    qDebug() << "contextMenuTriggered";
}
*/
