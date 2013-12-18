
#include "QEquipmentView.h"
#include "QEquipementItem.h"

QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    // ajoute le circuit arduino
    Equipement arduinoEquipement;
    arduinoEquipement.name = "Arduino MEGA";
    arduinoEquipement.type = "circuit";
    QEquipementItem* item = this->addEquipement(arduinoEquipement);
    item->setRect( -50.0, -50.0, 100.0, 100.0 );

    //ajoute un rectangle
/*    QGraphicsRectItem *item = new QGraphicsRectItem();
    item->setRect( -50.0, -50.0, 100.0, 100.0 );
    item->setRotation(160);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);

    //ajoute une image
    QGraphicsPixmapItem *pixItem = scene.addPixmap(QPixmap(":/equipement/light"));
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pixItem->setFlag(QGraphicsItem::ItemIsMovable, true);
*/
    //initialise la scene
    this->setScene(&scene);
    this->setRenderHints( QPainter::Antialiasing );
    this->show();

    this->setContextMenuPolicy(Qt::CustomContextMenu);

   // connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onContextMenu(const QPoint &)));
   connect(&scene, SIGNAL(selectionChanged()), this, SLOT(scnSelectionChanged()));
}

void QEquipmentView::onContextMenu(const QPoint & point)
{
    /*QMenu * menu = new QMenu("nom", this);
    // ajout des actions
    menu->move(event->x(), event->y());
    menu->show();*/
    PRINT("m");
}

QEquipementItem* QEquipmentView::addEquipement(const Equipement & equipement){

    //ajoute une image
    QEquipementItem *item = new QEquipementItem(equipement);
    item->setRect( -50.0, -50.0, 50.0, 50.0 );
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    scene.addItem( item );
    return item;
}

void QEquipmentView::scnSelectionChanged(){

    PRINT("scnSelectionChanged");
}
