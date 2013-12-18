/***********************************************************************
 * Module:  Controleur.h
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Declaration of the class Controleur
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Controleur_h)
#define __DATA_Controleur_h

class Pin;

class Controleur
{
public:
   int controleurId;
   QString adresseIp;
   
   Pin** reserve;
   Pin** libre;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif