/***********************************************************************
 * Module:  Client.h
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
 * Purpose: Declaration of the class Client
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Client_h)
#define __DATA_Client_h

class Client
{
public:
   int clientId;
   QString adresseIp;

   //SQL
   void bind(QSqlQuery & query);
   void bound(QSqlQuery & query);
protected:
private:

};

#endif