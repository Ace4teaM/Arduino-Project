/***********************************************************************
 * Module:  Server.cpp
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Implementation of the class Server
 ***********************************************************************/

#include "Server.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Server::bind(QSqlQuery & query){
       query.bindValue("server_id",QVariant(this->serverId));
       query.bindValue("ip",QVariant(this->ip));
       query.bindValue("mac",QVariant(this->mac));
       query.bindValue("name",QVariant(this->name));
       query.bindValue("pos_x",QVariant(this->posX));
       query.bindValue("pos_y",QVariant(this->posY));
       query.bindValue("pos_z",QVariant(this->posZ));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Server::bound(QSqlQuery & query){
       this->serverId = DataBase::getQueryInt(query,"server_id");
       this->ip = DataBase::getQueryString(query,"ip");
       this->mac = DataBase::getQueryString(query,"mac");
       this->name = DataBase::getQueryString(query,"name");
       this->posX = DataBase::getQueryFloat(query,"pos_x");
       this->posY = DataBase::getQueryFloat(query,"pos_y");
       this->posZ = DataBase::getQueryFloat(query,"pos_z");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Server::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("server_id");
   el.appendChild(dom.createTextNode(QVariant(this->serverId).toString()));
   parent.appendChild(el);
    el = dom.createElement("ip");
   el.appendChild(dom.createTextNode(QVariant(this->ip).toString()));
   parent.appendChild(el);
    el = dom.createElement("mac");
   el.appendChild(dom.createTextNode(QVariant(this->mac).toString()));
   parent.appendChild(el);
    el = dom.createElement("name");
   el.appendChild(dom.createTextNode(QVariant(this->name).toString()));
   parent.appendChild(el);
    el = dom.createElement("pos_x");
   el.appendChild(dom.createTextNode(QVariant(this->posX).toString()));
   parent.appendChild(el);
    el = dom.createElement("pos_y");
   el.appendChild(dom.createTextNode(QVariant(this->posY).toString()));
   parent.appendChild(el);
    el = dom.createElement("pos_z");
   el.appendChild(dom.createTextNode(QVariant(this->posZ).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Server::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("server_id")).length())
   {    this->serverId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("ip")).length())
   {    this->ip = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("mac")).length())
   {    this->mac = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("name")).length())
   {    this->name = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("pos_x")).length())
   {    this->posX = QVariant(list.at(0).toElement().text()).toFloat();    }
   if((list = parent.elementsByTagName("pos_y")).length())
   {    this->posY = QVariant(list.at(0).toElement().text()).toFloat();    }
   if((list = parent.elementsByTagName("pos_z")).length())
   {    this->posZ = QVariant(list.at(0).toElement().text()).toFloat();    }    

}