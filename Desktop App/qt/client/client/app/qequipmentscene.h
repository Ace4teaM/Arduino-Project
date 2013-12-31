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
#include "equipmessagedialog.h"

extern Application* app;

class QEquipmentScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QEquipmentScene();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
public slots:
    void on_deleteItem(bool);
    void on_sendMessage(bool);
};

#endif // QEQUIPMENTSCENE_H
