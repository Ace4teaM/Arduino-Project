/***********************************************************************
 * Module:  LedControler.h
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Declaration of the class LedControler
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_LedControler_h)
#define __DATA_LedControler_h

class Equipment;

class LedControler
{
public:
   int ledControlerId;
   int colorMode;
   
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