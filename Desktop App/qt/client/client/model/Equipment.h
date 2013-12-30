/***********************************************************************
 * Module:  Equipment.h
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Declaration of the class Equipment
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Equipment_h)
#define __DATA_Equipment_h

class Switcher;
class LedControler;
class Server;

class Equipment
{
public:
   int equipmentId;
   QString name;
   QString type;
   float posX;
   float posY;
   float posZ;
   
   Switcher** switcher;
   LedControler** ledControler;
   Server* server;

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