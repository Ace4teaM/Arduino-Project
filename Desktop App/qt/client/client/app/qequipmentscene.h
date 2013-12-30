#ifndef QEQUIPMENTSCENE_H
#define QEQUIPMENTSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QDialog>
#include <QLayout>

#include "../EquipProp.h"
#include "QEquipmentItem.h"
#include "equipdialog.h"

class QEquipmentScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QEquipmentScene();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
/*    void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
public slots:
    void contextMenuTriggered(QAction * action);*/
};

#endif // QEQUIPMENTSCENE_H
