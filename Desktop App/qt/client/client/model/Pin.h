/***********************************************************************
 * Module:  Pin.h
 * Author:  developpement
 * Modified: dimanche 22 d�cembre 2013 09:19:05
 * Purpose: Declaration of the class Pin
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Pin_h)
#define __DATA_Pin_h

class Controler;
class Equipment;

class Pin
{
public:
   int pinId;
   QString pinType;
   int pinNum;
   
   Controler** reserve;
   Equipment** Requis;
   Controler** libre;

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