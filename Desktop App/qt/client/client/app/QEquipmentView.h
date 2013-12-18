#ifndef QEQUIPMENTVIEW_H
#define QEQUIPMENTVIEW_H

#include "result.h"
#include "qequipementitem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "../model/Equipement.h"
#include "../model/Client.h"
#include "../model/Pin.h"

class QEquipmentView : public QGraphicsView{
    Q_OBJECT

public:
    QEquipmentView(QWidget *parent);
    QGraphicsScene scene;
    QEquipementItem* addEquipement(const Equipement & equip);
private slots:
    void onContextMenu(const QPoint & point);
    void scnSelectionChanged();
//protected:
//    QGraphicsScene scene;
};

#endif // QEQUIPMENTVIEW_H
