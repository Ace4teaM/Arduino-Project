/***********************************************************************
 * Module:  Switcher.h
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
 * Purpose: Declaration of the class Switcher
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Switcher_h)
#define __DATA_Switcher_h

class Equipment;

class Switcher
{
public:
   int switcherId;
   bool on;
   
   Equipment* equipment;

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