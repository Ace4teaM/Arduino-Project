/***********************************************************************
 * Module:  Client.h
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
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