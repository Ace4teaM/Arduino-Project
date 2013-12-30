/***********************************************************************
 * Module:  Server.h
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Declaration of the class Server
 ***********************************************************************/

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "../app/DataBase.h"

class DataBase;

#if !defined(__DATA_Server_h)
#define __DATA_Server_h

class Equipment;

class Server
{
public:
   int serverId;
   QString ip;
   QString mac;
   QString name;
   float posX;
   float posY;
   float posZ;
   
   Equipment** equipment;

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