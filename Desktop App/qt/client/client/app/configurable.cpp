#include "configurable.h"

/*---------------------------------------------------------------------------
    ConfigParam
---------------------------------------------------------------------------*/

/**
  @brief Construit un paramétre
  @param value Valeur par défaut
  @param title Titre du paramétre
*/
ConfigParam::ConfigParam(const QString value,const QString title){
    this->value = value;
    this->title= title;
    this->type = ConfigParam::TextValueType;
}

/**
  @brief Construit un paramétre
  @param value Valeur par défaut
  @param title Titre du paramétre
  @param type Type du paramètre, peut prendre l'une des valeurs suivantes:
*/
ConfigParam::ConfigParam(const QString value,const QString title,const int type){
    this->value = value;
    this->title= title;
    this->type = type;
}

/**
  @brief Obtient la valeur du paramètre
  @return Valeur en cours du paramétre
*/
const QString& ConfigParam::getValue() const{
    return this->value;
}

/**
  @brief Obtient une description courte du paramètre
  @return Description du paramétre
*/
const QString& ConfigParam::getTitle() const{
    return this->title;

}

/**
  @brief Obtient le type du paramètre
  @return Type, une des valeurs de l'énumeration ConfigParam::Type
*/
const int ConfigParam::getType() const{
    return this->type;

}

const QString& ConfigParam::setValue(const QString& v){
    return this->value = v;
}

const QString& ConfigParam::setTitle(const QString& v){
    return this->title = v;
}
const int ConfigParam::setType(int v){
    return this->type = v;
}


/*---------------------------------------------------------------------------
    ConfigXmlFile
---------------------------------------------------------------------------*/

/**
  @brief Enregistre les parametres dans un fichier de configuration xml

*/
bool ConfigXmlFile::save(const QString& filename,Configurable* config){

#ifdef _DEBUG
    QPRINT("save config <"+config->getConfigName()+"> to: "+filename);
#endif
    QDomDocument doc;
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly)){
        return QRESULT_DESC(Result::EC_OPEN_CFG_FILE,f.errorString());
    }
    doc.setContent(&f);

    f.close();

    // obtient noeud principale
    QDomElement root = doc.documentElement().firstChildElement(config->getConfigName());

    //crée l'élément si il n'existe pas
    if(root.isNull()){
        root = doc.createElement(config->getConfigName());
        if(!root.isNull())
            doc.documentElement().appendChild(root);
    }
    if(root.isNull())
        return QRESULT_DESC(Result::EC_XML_FILE_EDIT,"Création du noeud "+config->getConfigName());

    //noeuds enfants
    ConfigParamList list;
    config->configRead(list);

    //scan les parametres
    for(ConfigParamList::const_iterator cur = list.begin(); cur != list.end(); cur++){
        QString name = cur->first;

        // obtient noeud enfant
        QDomElement old_child = root.firstChildElement(name);

        //crée l'élément si il n'existe pas
        QDomElement child = doc.createElement(name);
        if(!child.isNull())
            root.appendChild(child);
        if(child.isNull())
            return QRESULT_DESC(Result::EC_XML_FILE_EDIT,"Création du noeud "+name);

        //définit le texte
        QDomText text = doc.createTextNode(cur->second->getValue());
        child.appendChild(text);

        //insert / remplace le nouveau noeud
        if(!old_child.isNull())
            root.replaceChild(child,old_child);
        else
            root.appendChild(child);
    }

    //réouvre le fichier en écriture
    QTextStream sortie;
    f.setFileName(filename);
    if(!f.open(QIODevice::WriteOnly)){
        return QRESULT_DESC(Result::EC_OPEN_CFG_FILE,f.errorString());
    }
    sortie.setDevice(&f); // association du flux au fichier

    // insertion en début de document de <?xml version="1.0" ?>
//    QDomNode headNode = doc.createProcessingInstruction("xml","version=\"1.0\"");
//    doc.insertBefore(headNode, doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(sortie, 2);
    f.close();

    return QRESULT_OK;
}

/**
  @brief Fichier de configuration XML
*/
bool ConfigXmlFile::load(const QString& filename,Configurable* config,ConfigParamList& list){

#ifdef _DEBUG
    QPRINT("Load Config '"+config->getConfigName()+"' from "+filename);
#endif
    QDomDocument doc;
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly)){
        return QRESULT_DESC(Result::EC_OPEN_CFG_FILE,f.errorString());
    }
    doc.setContent(&f);

    f.close();

    QDomElement root = doc.documentElement().firstChildElement(config->getConfigName());
    if(root.isNull())
        return false;

    //scan les elements enfants
    for(ConfigParamList::const_iterator cur = list.begin(); cur != list.end(); cur++){
        QString name = cur->first;
        QDomElement child = root.firstChildElement(name);
        if(!child.isNull()){
            cur->second->value = child.text().trimmed();
#ifdef _DEBUG
            QPRINT("loadConfig >> "+config->getConfigName()+"."+name+" : "+cur->second->value);
#endif
        }
#ifdef _DEBUG
        else
            QPRINT("loadConfig >> "+config->getConfigName()+"."+name+" [NOT FOUND]");
#endif
    }

    return true;
}

/**
  @brief Charge les données d'une section de configuration XML
*/
bool ConfigXmlFile::load(const QString& filename,const QString& section_name,ConfigParamList& list){

#ifdef _DEBUG
    QPRINT("Load Config '"+section_name+"' from "+filename);
#endif
    QDomDocument doc;
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly)){
        return QRESULT_DESC(Result::EC_OPEN_CFG_FILE,f.errorString());
    }
    doc.setContent(&f);

    f.close();

    QDomElement root = doc.documentElement().firstChildElement(section_name);
    if(root.isNull())
        return false;

    //scan les elements enfants
    QDomElement child = root.firstChildElement();
    while(!child.isNull()){
        QString name = child.tagName();
        QString value = child.text().trimmed();
        if(!name.isEmpty()){
            list[name] = new ConfigParam(value,name);
#ifdef _DEBUG
            QPRINT("loadConfig >> "+section_name+"."+name+" : "+value);
#endif
        }
        child = child.nextSiblingElement();
    }

    return true;
}

/**
  @brief Charge les données d'une section de configuration XML
  @param filename     Emplacement du fichier XML
  @param section_name Nom de la section
  @param list         Pointeur sur la liste associative recevant les données
  @return Résultat de procédure
*/
bool ConfigXmlFile::load(const QString& filename,const QString& section_name,QAssocList& list){

#ifdef _DEBUG
    QPRINT("Load Config '"+section_name+"' from "+filename);
#endif

    QDomDocument doc;
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly)){
        QPRINT(QDir::currentPath());
        QPRINT(filename);
        return QRESULT_DESC(Result::EC_OPEN_CFG_FILE,f.errorString());
    }
    doc.setContent(&f);

    f.close();

    QDomElement root = doc.documentElement().firstChildElement(section_name);
    if(root.isNull())
        return false;

    //scan les elements enfants
    QDomElement child = root.firstChildElement();
    while(!child.isNull()){
        QString name = child.tagName();
        QString value = child.text().trimmed();
        if(!name.isEmpty()){
            list[name] = value;
#ifdef _DEBUG
            QPRINT("loadConfig >> "+section_name+"."+name+" : "+value);
#endif
        }
        child = child.nextSiblingElement();
    }

    return true;
}

/*---------------------------------------------------------------------------
    Configurable
---------------------------------------------------------------------------*/

/**
  @brief Initialise dans une liste de parametres à partir des widgets editables trouvés
  @param widget Widget parent
  @param list Liste recevant les parametres
*/
void Configurable::configFromWidget(QObject* widget,ConfigParamList& paramList){

    //parametres de configuration
    Configurable::configFromNextWidget(widget,paramList);
}

/**
  @copydoc Configurable::configFromWidget
*/
void Configurable::configFromNextWidget(QObject* cur,ConfigParamList& paramList){

    //parametres de configuration
    const QObjectList& list = cur->children();
    for(int i=0;i<list.size();i++)
    {
        QObject* child = list.at(i);
        if(!child->objectName().isEmpty() && child->isWidgetType())
        {
            QString value;

            // QLineEdit ?
            QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child);
            if(lineEdit)
               value = lineEdit->text();

            // QComboBox ?
            QComboBox *comboBox = qobject_cast<QComboBox *>(child);
            if(comboBox)
                value = comboBox->currentText();

            // QSpinBox ?
            QSpinBox *spinBox = qobject_cast<QSpinBox *>(child);
            if(spinBox)
                value = spinBox->text();

            // QDoubleSpinBox ?
            QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(child);
            if(doubleSpinBox)
                value = doubleSpinBox->text();

            // QTextEdit ?
            QTextEdit *textEdit = qobject_cast<QTextEdit *>(child);
            if(textEdit)
                value = textEdit->toPlainText();

            // QPlainTextEdit ?
            QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit *>(child);
            if(plainTextEdit)
                value = plainTextEdit->toPlainText();

            // QTimeEdit ?
            QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(child);
            if(timeEdit)
                value = timeEdit->text();

            // QDateTimeEdit ?
            QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit *>(child);
            if(dateTimeEdit)
                value = timeEdit->text();

            // QDateEdit ?
            QDateEdit *dateEdit = qobject_cast<QDateEdit *>(child);
            if(dateEdit)
                value = dateEdit->text();

            // QDial ?
            QDial *dial = qobject_cast<QDial *>(child);
            if(dial)
                value = QString::number(dial->value());

            // QSlider ?
            QSlider *slider = qobject_cast<QSlider *>(child);
            if(slider)
                value = QString::number(slider->value());

            //sauvegarde la valeur
            if(!value.isNull()){
/*#ifdef _DEBUG
                QPRINT("loadConfig >> "+child->objectName()+"="+value);
#endif*/
                if(paramList.find(child->objectName()) != paramList.end())
                    paramList[child->objectName()]->setValue(value);
                else
                    paramList[child->objectName()] = new ConfigParam(value,"");
            }
        }
        Configurable::configFromNextWidget(child,paramList);
    }
}

/**
  @brief Initialise un widget avec une liste de parametres
  @param widget Widget parent
  @param list Liste des parametres
  @remarks Les noms des widgets doivent correspondres avec les noms de paramètres
*/
void Configurable::configToWidget(QObject* widget,ConfigParamList& list){

    //scan les elements enfants
    for(ConfigParamList::const_iterator cur = list.begin(); cur != list.end(); cur++){
        QString name = cur->first;
        QString value = cur->second->getValue();
        QWidget* child = widget->findChild<QWidget*>(name);
        if(child==0){
            QPRINT("configToWidget: "+name+" not found");
            continue;
        }

        // QLineEdit ?
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child);
        if(lineEdit){
           lineEdit->setText(value);
           continue;
        }

        // QComboBox ?
        QComboBox *comboBox = qobject_cast<QComboBox *>(child);
        if(comboBox){
            comboBox->setCurrentIndex(comboBox->findText(value));
            continue;
         }

        // QSpinBox ?
        QSpinBox *spinBox = qobject_cast<QSpinBox *>(child);
        if(spinBox){
            spinBox->setValue(value.toInt());
            continue;
         }


        // QDoubleSpinBox ?
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox *>(child);
        if(doubleSpinBox){
            doubleSpinBox->setValue(value.toInt());
            continue;
         }

        // QTextEdit ?
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(child);
        if(textEdit){
            textEdit->setPlainText(value);
            continue;
         }

        // QPlainTextEdit ?
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit *>(child);
        if(plainTextEdit){
            plainTextEdit->setPlainText(value);
            continue;
         }

        // QTimeEdit ?
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(child);
        if(timeEdit){
            timeEdit->setTime(QTime::fromString(value));
            continue;
         }

        // QDateTimeEdit ?
        QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit *>(child);
        if(dateTimeEdit){
            timeEdit->setDateTime(QDateTime::fromString(value));
            continue;
         }

        // QDateEdit ?
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(child);
        if(dateEdit){
            dateEdit->setDate(QDate::fromString(value));
            continue;
         }

        // QDial ?
        QDial *dial = qobject_cast<QDial *>(child);
        if(dial){
            dial->setValue(value.toInt());
            continue;
         }

        // QSlider ?
        QSlider *slider = qobject_cast<QSlider *>(child);
        if(slider){
            slider->setValue(value.toInt());
            continue;
         }

    }

}

QString Configurable::get(ConfigParamList& list,const QString& name){
    if(list.find(name) != list.end()){
        return list[name]->getValue();
    }
    return QString();
}

QString Configurable::set(ConfigParamList& list,const QString& name,ConfigParam param){
    if(list.find(name) != list.end()){
        list[name]->setValue(param.getValue());
        list[name]->setTitle(param.getTitle());
    }
    else
        list[name] = new ConfigParam(param.getValue(),param.getTitle());

    return param.getValue();
}

QString Configurable::set(ConfigParamList& list,const QString& name,const QString& value){
    if(list.find(name) != list.end())
        list[name]->setValue(value);
    else
        list[name] = new ConfigParam(value,name);

    return value;
}

/*---------------------------------------------------------------------------
    Configuration
---------------------------------------------------------------------------
Configuration::Configuration(const QString& name,const QString& title){
    this->name  = name;
    this->title = title;
}

const QString Configuration::getConfigTitle(){
    return this->title;
}

const QString Configuration::getConfigName(){
    return this->name;
}

ConfigParamList& Configuration::getConfigParams(){
    return this->configParams;
}

bool Configuration::configUpdate(){
    return ConfigXmlFile::save("config.xml",this);
}
*/
