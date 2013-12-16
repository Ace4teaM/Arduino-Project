#ifndef QEQUIPMENTVIEW_H
#define QEQUIPMENTVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class QEquipmentView : public QGraphicsView{
public:
    QEquipmentView(QWidget *parent);
    QGraphicsScene scene;
//protected:
//    QGraphicsScene scene;
};

#endif // QEQUIPMENTVIEW_H
