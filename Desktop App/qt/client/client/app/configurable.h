#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QPlainTextEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QDial>
#include <QSlider>
#include <QDir>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QString>
#include <QTextStream>
#include <map>
#include "result.h"
#include "qassoclist.h"

/**
  @brief Paramètre de configuration
*/
class ConfigParam
{
public:
    ConfigParam(const QString value,const QString title);
    ConfigParam(const QString value,const QString title,const int type);

    enum Type{
        TextValueType,
        FilePathType
    };

    const QString& getValue()const;
    const QString& getTitle()const;
    const int getType()const;

    const QString& setValue(const QString&);
    const QString& setTitle(const QString&);
    const int setType(int);

    QString title;
    QString value;
    int type;
};

/**
  @brief Liste de paramètres
*/
typedef std::map<QString,ConfigParam*> ConfigParamList;

/**
  @brief Interface de configuration
  @remarks Permet une interface générique avec les fichiers de configuration
*/
class Configurable
{
public:
    virtual const QString getConfigTitle() = 0;
    virtual const QString getConfigName() = 0;
/*    virtual ConfigParamList& getConfigParams() = 0;
    virtual bool configUpdate() = 0;*/
    virtual bool configUpdate(ConfigParamList& list) = 0;
    virtual bool configRead(ConfigParamList& list) = 0;
    //static...
    static void configFromWidget(QObject* widget,ConfigParamList& list);
    static void configFromNextWidget(QObject* cur,ConfigParamList& list);
    static void configToWidget(QObject* widget,ConfigParamList& paramList);
    //
    static QString get(ConfigParamList& list,const QString& name);
    static QString set(ConfigParamList& list,const QString& name,ConfigParam param);
    static QString set(ConfigParamList& list,const QString& name,const QString& value);
};

/**
  @brief Gestion des flux de paramètres dans un fichier de configuration XML
*/
class ConfigXmlFile
{
public:
    static bool save(const QString& filename,Configurable* config);
    static bool load(const QString& filename,Configurable* config,ConfigParamList& list);
    static bool load(const QString& filename,const QString& section_name,ConfigParamList& list);
    static bool load(const QString& filename,const QString& section_name,QAssocList& list);
};

/**
  @brief Classe de configuration
  @remarks Permet une interface générique avec les fichiers de configuration

class Configuration : public Configurable
{
public:
    Configuration(const QString& name,const QString& title);
    const QString getConfigTitle();
    const QString getConfigName();
    ConfigParamList& getConfigParams();
    bool configUpdate();
    QString get(const QString& name);
    QString set(const QString& name,ConfigParam param);
    QString set(const QString& name,const QString& value);
    ConfigParamList configParams;
    QString name;
    QString title;
};*/


#endif // CONFIGURABLE_H
