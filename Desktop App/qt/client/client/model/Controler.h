/***********************************************************************
 * Module:  Controler.h
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
 * Purpose: Declaration of the class Controler
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Controler_h)
#define __DATA_Controler_h

class Pin;

class Controler
{
public:
   int controlerId;
   QString ip;
   QString mac;
   
   Pin** reserve;
   Pin** libre;

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