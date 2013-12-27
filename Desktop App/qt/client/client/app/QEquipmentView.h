#ifndef QEQUIPMENTVIEW_H
#define QEQUIPMENTVIEW_H

#include "result.h"
#include "qequipmentitem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "QEquipmentScene.h"
#include "../model/Equipment.h"
#include "../model/Client.h"
#include "../model/Pin.h"
#include <l1/riff.h>
#include <l1/memory.h>

class QEquipmentView : public QGraphicsView{
    Q_OBJECT

public:
    QEquipmentView(QWidget *parent);
    QEquipmentScene scene;
    QEquipmentItem* addEquipment(const Equipment & equip);
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

typedef struct _RIFF_EQUIP{
    int id;
    char name[64];
    char type[32];
}RIFF_EQUIP;

#endif // QEQUIPMENTVIEW_H
