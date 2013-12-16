/***********************************************************************
 * Module:  Pin.h
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:57:56
 * Purpose: Declaration of the class Pin
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Pin_h)
#define __DATA_Pin_h

class Equipement;
class Controleur;

class Pin
{
public:
   int pinId;
   QString pinType;
   int pinNum;
   
   Equipement** Requis;
   Controleur* reserve;
   Controleur* libre;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif