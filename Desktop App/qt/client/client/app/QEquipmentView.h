#ifndef QEQUIPMENTVIEW_H
#define QEQUIPMENTVIEW_H

#include "result.h"
#include "qequipmentitem.h"
#include "qserveritem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "QEquipmentScene.h"
#include "../model/Equipment.h"
#include "../model/Client.h"
#include "riff.h"
#include <l1/riff.h>
#include <l1/memory.h>

class QEquipmentView : public QGraphicsView{
    Q_OBJECT

public:
    QEquipmentView(QWidget *parent);
    QEquipmentScene scene;
    QEquipmentItem* addEquipment(const Equipment & equip);
    QServerItem* addServer(const Server & server);
    bool rearrangeView();
    /**
      @brief Obtient le circuit principal
    */
    QEquipmentItem* getCircuit();
    /**
      @brief Sauvegarde le schema dans un document XML
      @param dom Document XML
      @return Résultat de procèdure
    */
    bool toXML(QDomDocument & dom);
    /**
      @brief Charge un schema depuis un document XML
      @param dom Document XML
      @return Résultat de procèdure
    */
    bool fromXML(QDomDocument & dom);
    /**
      @brief Charge un schema depuis un fichier RIFF
      @param mem Tampon mémoire
      @return Résultat de procèdure
    */
    bool fromRIFF(PTR* mem);
    /**
      @brief Sauvegarde le schema dans un fichier RIFF
      @param mem Tampon mémoire
      @return Résultat de procèdure
    */
    bool toRIFF(PTR* mem);
    /**
      @brief Réinitialise la scene
    */
    void reset();
private slots:
    void onContextMenu(const QPoint & point);
    void scnSelectionChanged();
//protected:
//    QGraphicsScene scene;
};

#endif // QEQUIPMENTVIEW_H
