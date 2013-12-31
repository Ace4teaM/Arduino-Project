#include "qequipmentscene.h"

QEquipmentScene::QEquipmentScene()
{
}

/**
 * @brief Affiche le dialogue de propriétés sur l'équipement
*/
void QEquipmentScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent){
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

    //récupére les infos sur l'équipement
    QEquipmentItem* item = dynamic_cast<QEquipmentItem*>(this->selectedItems().at(0));
    if(!item) return;

    qDebug() << item->getEquipment().name;

    // initialise le dialogue de proprietes
    EquipDialog *dialog = new EquipDialog(item->getEquipment());
    dialog->exec();
}

/**
 * @brief Affiche le menu contextuel de l'équipement
*/
void QEquipmentScene::contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent){
    QEquipmentItem* equip;
    QServerItem* server;

    if(this->selectedItems().count())
    {
        QGraphicsItem* i = this->selectedItems().at(0);
        //Equipement ?
        if( equip = dynamic_cast<QEquipmentItem*>(i) ){
            QMenu *menu = new QMenu();
            menu->addAction("Envoyer un message...",this,SLOT(on_sendMessage(bool)));
            menu->addAction("Supprimer",this, SLOT(on_deleteItem(bool)));
            menu->popup(contextMenuEvent->screenPos());
        }
        //Equipement ?
        else if( server = dynamic_cast<QServerItem*>(i) ){
            QMenu *menu = new QMenu();
            menu->addAction("Envoyer une commande...");
            menu->popup(contextMenuEvent->screenPos());
        }
    }
    contextMenuEvent->accept();
}

/**
 * @brief Supprime les éléments sélectionnés
 */
void QEquipmentScene::on_deleteItem(bool){
    for(int i=0;i<this->selectedItems().count();i++)
        this->removeItem(this->selectedItems().at(0));
}

/**
 * @brief Envoi un message
 */
void QEquipmentScene::on_sendMessage(bool){
    QEquipmentItem* equip = dynamic_cast<QEquipmentItem*>(this->selectedItems().at(0));
    EquipMessageDialog* dialog = new EquipMessageDialog(equip->getEquipment(),app->wnd);
    dialog->exec();
}

