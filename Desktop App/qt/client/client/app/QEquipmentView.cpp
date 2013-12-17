
#include "QEquipmentView.h"


QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    //ajoute un rectangle
    QGraphicsRectItem *item = new QGraphicsRectItem();
    item->setRect( -50.0, -50.0, 100.0, 100.0 );
    item->setRotation(160);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);

    //ajoute une image
    QGraphicsPixmapItem *pixItem = scene.addPixmap(QPixmap("equipement/light/image.png"));
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pixItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    //initialise la scene
    scene.addItem( item );
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

bool QEquipmentView::addEquipement(Equipement* equip){

    //ajoute une image
    QGraphicsPixmapItem *pixItem = scene.addPixmap(QPixmap("equipement/light/image.png"));
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pixItem->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void QEquipmentView::scnSelectionChanged(){

    PRINT("scnSelectionChanged");
}
