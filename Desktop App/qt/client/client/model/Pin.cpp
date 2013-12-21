/***********************************************************************
 * Module:  Pin.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Pin
 ***********************************************************************/

#include "Pin.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Pin::bind(QSqlQuery & query){
       query.bindValue("pin_id",QVariant(this->pinId));
       query.bindValue("pin_type",QVariant(this->pinType));
       query.bindValue("pin_num",QVariant(this->pinNum));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Pin::bound(QSqlQuery & query){
       this->pinId = DataBase::getQueryInt(query,"pin_id");
       this->pinType = DataBase::getQueryString(query,"pin_type");
       this->pinNum = DataBase::getQueryInt(query,"pin_num");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Pin::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("pin_id");
   el.appendChild(dom.createTextNode(QVariant(this->pinId).toString()));
   parent.appendChild(el);
    el = dom.createElement("pin_type");
   el.appendChild(dom.createTextNode(QVariant(this->pinType).toString()));
   parent.appendChild(el);
    el = dom.createElement("pin_num");
   el.appendChild(dom.createTextNode(QVariant(this->pinNum).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Pin::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("pin_id")).length())
   {    this->pinId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("pin_type")).length())
   {    this->pinType = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("pin_num")).length())
   {    this->pinNum = list.at(0).toElement().text().toInt();    }    

}