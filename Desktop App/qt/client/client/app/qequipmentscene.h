#ifndef QEQUIPMENTSCENE_H
#define QEQUIPMENTSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QDialog>
#include <QLayout>

#include "../EquipProp.h"
#include "QEquipmentItem.h"

class QEquipmentScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QEquipmentScene();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif // QEQUIPMENTSCENE_H
