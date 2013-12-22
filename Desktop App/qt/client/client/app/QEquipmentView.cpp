
#include "QEquipmentView.h"
#include "QEquipementItem.h"

QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    // ajoute le circuit arduino
    Equipment arduinoEquipment;
    arduinoEquipment.equipmentId = 1;
    arduinoEquipment.name = "Arduino MEGA";
    arduinoEquipment.type = "circuit";
    QEquipmentItem* item = this->addEquipment(arduinoEquipment);
    //item->setRect( -50.0, -50.0, 100.0, 100.0 );

    //ajoute un rectangle
/*    QGraphicsRectItem *item = new QGraphicsRectItem();
    item->setRect( -50.0, -50.0, 100.0, 100.0 );
    item->setRotation(160);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);

    //ajoute une image
    QGraphicsPixmapItem *pixItem = scene.addPixmap(QPixmap(":/equipement/light"));
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pixItem->setFlag(QGraphicsItem::ItemIsMovable, true);
*/
    //initialise la scene
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

QEquipmentItem* QEquipmentView::addEquipment(const Equipment & equipment)
{
    //ajoute une image
    QEquipmentItem *item = new QEquipmentItem(equipment);
    item->setRect( -50.0, -50.0, 50.0, 50.0 );
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);

    scene.addItem( item );
    return item;
}

void QEquipmentView::scnSelectionChanged(){
    PRINT("scnSelectionChanged");
}

bool QEquipmentView::toXML(QDomDocument & dom)
{
    QList<QGraphicsItem*> list = scene.items();
    QList<QGraphicsItem*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i){
        QEquipmentItem* item = (QEquipmentItem*)*i;
        //crée l'élément XML
        QDomElement el = dom.createElement(item->getEquipment().type);
        el.setAttribute("id",item->getEquipment().equipmentId);
        item->getEquipment().bindXML(el);
        dom.documentElement().appendChild(el);
    }
    return QRESULT_OK();
}

bool QEquipmentView::fromXML(QDomDocument & dom)
{
    //supprime le contenu en cours
    scene.clear();

    //charge le contenu
    QDomElement el = dom.documentElement().firstChildElement();
    while(!el.isNull()){
        Equipment equip;
        equip.boundXML(el);
        this->addEquipment(equip);
        el = el.nextSiblingElement();
    }
    return QRESULT_OK();
}

bool QEquipmentView::rearrangeView()
{
    QList<QGraphicsItem*> list = scene.items();
    QList<QGraphicsItem*>::iterator i;

    QEquipmentItem* circuit = this->getCircuit();
    if(!circuit)
        return QRESULT_DESC(Result::Failed,"CIRCUIT_NOT_FOUND");

    int max = list.count()-1;//maximum d'items enfants au circuit
    qreal dist = circuit->boundingRect().width() * 2.0;
    dist = dist * (1.0 * (max/10.0));

    //placement
    int x=0;
    for (i = list.begin(); i != list.end(); ++i){
        QEquipmentItem* item = (QEquipmentItem*)*i;
        if(item->getEquipment().type != "circuit")
        {
            item->setPos(circuit->pos().rx() + (dist*cos((2*M_PI)*((1.0/max)*x))),circuit->pos().ry() + (dist*sin((2*M_PI)*((1.0/max)*x))));
            x++;
        }
    }

    return QRESULT_OK();
}

QEquipmentItem* QEquipmentView::getCircuit()
{
    QList<QGraphicsItem*> list = scene.items();
    QList<QGraphicsItem*>::iterator i;
    for (i = list.begin(); i != list.end(); ++i){
        QEquipmentItem* item = (QEquipmentItem*)*i;
        if(item->getEquipment().type == "circuit")
        {
            return item;
        }
    }
    return NULL;
}
