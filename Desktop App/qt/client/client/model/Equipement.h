/***********************************************************************
 * Module:  Equipement.h
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
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
   
   Pin** Requis;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif