/***********************************************************************
 * Module:  Equipement.h
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Declaration of the class Equipement
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Equipement_h)
#define __DATA_Equipement_h

class Pin;

class Equipement
{
public:
   int equipementId;
   QString name;
   QString type;
   
   Pin** Requis;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif