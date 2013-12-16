
#include "QEquipmentView.h"


QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    QGraphicsRectItem *item = new QGraphicsRectItem();
    item->setRect( -50.0, -50.0, 100.0, 100.0 );
    item->setRotation(160);

    scene.addItem( scene.addPixmap(QPixmap(":/equipement/light/image.png")) );

    scene.addItem( item );
    this->setScene(&scene);
    this->setRenderHints( QPainter::Antialiasing );
    this->show();

    //connect(table, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
}
/*
void QEquipmentView::onContextMenu(const QPoint & point)
{
    if(event->x() > 0 && event->x() < width() &&
       event->y() > 0 && event->y() < height() &&
       event->button() == Qt::RightButton)
    {
        QMenu * menu = new QMenu("nom", this);
        // ajout des actions
        menu->move(event->x(), event->y());
        menu->show();
    }
}
*/
