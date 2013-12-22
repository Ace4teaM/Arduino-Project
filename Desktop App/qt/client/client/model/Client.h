/***********************************************************************
 * Module:  Client.h
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
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
   QString ip;

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