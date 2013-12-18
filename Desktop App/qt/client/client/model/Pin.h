/***********************************************************************
 * Module:  Pin.h
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Declaration of the class Pin
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Pin_h)
#define __DATA_Pin_h

class Controleur;
class Equipement;

class Pin
{
public:
   int pinId;
   QString pinType;
   int pinNum;
   
   Controleur** reserve;
   Equipement** Requis;
   Controleur** libre;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif