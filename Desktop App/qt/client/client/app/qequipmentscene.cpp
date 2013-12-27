#include "qequipmentscene.h"

QEquipmentScene::QEquipmentScene()
{
}

void QEquipmentScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent){
    qDebug() << QString("mouseDoubleClickEvent");
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);

    //récupére les infos sur l'équipement
    QEquipmentItem* item = dynamic_cast<QEquipmentItem*>(this->selectedItems().at(0));
    if(!item) return;

    qDebug() << item->getEquipment().name;

    // initialise le dialogue de proprietes
    QDialog *dialog = new QDialog();
    dialog->setModal(true);
//    dialog->setSizePolicy();
    dialog->exec();
/*    EquipProp* baseProp = new EquipProp(dialog);
    dialog->layout()->addWidget(baseProp);*/
}
