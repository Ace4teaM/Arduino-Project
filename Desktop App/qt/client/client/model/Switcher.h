/***********************************************************************
 * Module:  Switcher.h
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
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