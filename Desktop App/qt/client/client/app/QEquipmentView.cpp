
#include "QEquipmentView.h"


QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene scene;
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    QGraphicsEllipseItem *item = new QGraphicsEllipseItem();
    item->setRect( -50.0, -50.0, 100.0, 100.0 );

    scene.addPixmap(QPixmap(":/equipement/light/image.png"));

    scene.addItem( item );
    this->setScene(&scene);
    this->setRenderHints( QPainter::Antialiasing );
    this->show();
}
