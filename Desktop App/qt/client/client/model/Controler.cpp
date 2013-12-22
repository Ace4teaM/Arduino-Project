/***********************************************************************
 * Module:  Controler.cpp
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
 * Purpose: Implementation of the class Controler
 ***********************************************************************/

#include "Controler.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Controler::bind(QSqlQuery & query){
       query.bindValue("controler_id",QVariant(this->controlerId));
       query.bindValue("ip",QVariant(this->ip));
       query.bindValue("mac",QVariant(this->mac));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Controler::bound(QSqlQuery & query){
       this->controlerId = DataBase::getQueryInt(query,"controler_id");
       this->ip = DataBase::getQueryString(query,"ip");
       this->mac = DataBase::getQueryString(query,"mac");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Controler::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("controler_id");
   el.appendChild(dom.createTextNode(QVariant(this->controlerId).toString()));
   parent.appendChild(el);
    el = dom.createElement("ip");
   el.appendChild(dom.createTextNode(QVariant(this->ip).toString()));
   parent.appendChild(el);
    el = dom.createElement("mac");
   el.appendChild(dom.createTextNode(QVariant(this->mac).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Controler::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("controler_id")).length())
   {    this->controlerId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("ip")).length())
   {    this->ip = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("mac")).length())
   {    this->mac = list.at(0).toElement().text();    }    

}