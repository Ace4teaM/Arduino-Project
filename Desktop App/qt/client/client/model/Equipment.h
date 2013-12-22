/***********************************************************************
 * Module:  Equipment.h
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
 * Purpose: Declaration of the class Equipment
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Equipment_h)
#define __DATA_Equipment_h

class Pin;
class Switcher;
class LedControler;

class Equipment
{
public:
   int equipmentId;
   QString name;
   QString type;
   float posX;
   float posY;
   float posZ;
   
   Pin** Requis;
   Switcher** switcher;
   LedControler** ledControler;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
   //XML
   void boundXML(QDomElement & parent);
   void bindXML(QDomElement & parent);
protected:
private:

};

#endif