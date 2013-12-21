/***********************************************************************
 * Module:  Client.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Client
 ***********************************************************************/

#include "Client.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Client::bind(QSqlQuery & query){
       query.bindValue("client_id",QVariant(this->clientId));
       query.bindValue("adresse_ip",QVariant(this->adresseIp));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Client::bound(QSqlQuery & query){
       this->clientId = DataBase::getQueryInt(query,"client_id");
       this->adresseIp = DataBase::getQueryString(query,"adresse_ip");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Client::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("client_id");
   el.appendChild(dom.createTextNode(QVariant(this->clientId).toString()));
   parent.appendChild(el);
    el = dom.createElement("adresse_ip");
   el.appendChild(dom.createTextNode(QVariant(this->adresseIp).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Client::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("client_id")).length())
   {    this->clientId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("adresse_ip")).length())
   {    this->adresseIp = list.at(0).toElement().text();    }    

}