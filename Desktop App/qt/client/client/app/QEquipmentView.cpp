
#include "QEquipmentView.h"
#include "QEquipmentItem.h"

QEquipmentView::QEquipmentView(QWidget *parent) : QGraphicsView(parent)
{
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    // ajoute le circuit arduino
    Equipment arduinoEquipment;
    arduinoEquipment.equipmentId = 1;
    arduinoEquipment.name = "Arduino MEGA";
    arduinoEquipment.type = "circuit";
    arduinoEquipment.posX = 0;
    arduinoEquipment.posY = 0;
    arduinoEquipment.posZ = 0;
    QEquipmentItem* item = this->addEquipment(arduinoEquipment);

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
    item->setPos(equipment.posX,equipment.posY);

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
        //atualise la position
        item->getEquipment().posX = item->pos().rx();
        item->getEquipment().posY = item->pos().ry();
        //
        item->getEquipment().bindXML(el);
        dom.documentElement().appendChild(el);
    }
    return QRESULT_OK();
}

bool QEquipmentView::fromXML(QDomDocument & dom)
{
    //supprime le contenu en cours
    this->reset();

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

/**
  @brief Charge un schema depuis un fichier RIFF
  @param mem Tampon mémoire
  @return Résultat de procèdure
*/
bool QEquipmentView::fromRIFF(PTR* mem){
    RIFF riff;

    //supprime le contenu de la scene
    this->reset();

    //lit l'entete
    if(!riff_read(mem,&riff))
        return false;

    //Vérifie l'en-tete
    if(!(riff.id[0] == 'R' && riff.id[1] == 'I' && riff.id[2] == 'F' && riff.id[3] == 'F'))
        return QRESULT_DESC(Result::Failed, Result::RiffInvalidHeader);
    if(mem->ptr+riff.size > mem->down)
        return QRESULT_DESC(Result::Failed, Result::RiffInvalidTagSize);

    //lit les chunk
    char tag[4];
    unsigned int tag_size;
    while(mem->ptr<mem->down && riff_read_tag(mem,tag,&tag_size)){
        qDebug() << "tag=" << tag[0] << tag[1] << tag[2] << tag[3];
        qDebug() << "tag_size=" << tag_size;
        if(mem->ptr+tag_size > mem->down)
            return QRESULT_DESC(Result::Failed, Result::RiffInvalidTagSize);
        if(memcmp("EQUIP",tag,sizeof(tag)) == 0 ){
            qDebug() << "EQUIP tag...";
            //Charge l'équipement
            RIFF_EQUIP equip;
            equip.id = btoi(mem);
            bread(mem,equip.name,sizeof(equip.name));
            bread(mem,equip.type,sizeof(equip.type));
            //Ajoute l'équipement à la scene
            Equipment qequip;
            qequip.equipmentId = equip.id;
            qequip.name = QString(equip.name);
            qequip.type = QString(equip.type);
            QPRINT(qequip.type);
            qequip.posX = qequip.posY = qequip.posZ = 0;
            this->addEquipment(qequip);
        }
        else{
            qDebug() << "IGNORE tag";
            mem->ptr += tag_size;
        }
        qDebug() << "offset=" << boffset(mem);
    }

    return QRESULT_OK();
}

/**
  @brief Sauvegarde le schema dans un fichier RIFF
  @param mem Tampon mémoire
  @return Résultat de procèdure
*/
bool QEquipmentView::toRIFF(PTR* mem)
{
    RIFF riff = {{'R','I','F','F'},sizeof(RIFF_HEADER)};

    QList<QGraphicsItem*> list = scene.items();
    QList<QGraphicsItem*>::iterator i;

    //ecrit les données
    if(!riff_write(mem,&riff))
        return false;

    for (i = list.begin(); i != list.end(); ++i){
        QEquipmentItem* item = (QEquipmentItem*)*i;
        //initialise la structure de l'item
        RIFF_EQUIP equip;
        equip.id = item->getEquipment().equipmentId;
        strcpy(equip.name,item->getEquipment().name.toLatin1().data());
        strcpy(equip.type,item->getEquipment().type.toLatin1().data());
        //ecrit en mémoire
        if(!riff_write_tag(mem,"EQUI",sizeof(RIFF_EQUIP)))
            return false;
        if(!itob(mem,equip.id))
            return false;
        if(!bwrite(mem,equip.name,sizeof(equip.name)))
            return false;
        if(!bwrite(mem,equip.type,sizeof(equip.type)))
            return false;
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

/**
  @brief Réinitialise la scene
*/
void QEquipmentView::reset(){
    //supprime le contenu de la scene
    scene.clear();
}

/**
  @brief Obtient le circuit principal
*/
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
