/***********************************************************************
 * Module:  Switcher.cpp
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Implementation of the class Switcher
 ***********************************************************************/

#include "Switcher.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Switcher::bind(QSqlQuery & query){
       query.bindValue("switcher_id",QVariant(this->switcherId));
       query.bindValue("on",QVariant(this->on));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Switcher::bound(QSqlQuery & query){
       this->switcherId = DataBase::getQueryInt(query,"switcher_id");
       this->on = (bool)DataBase::getQueryInt(query,"on");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Switcher::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("switcher_id");
   el.appendChild(dom.createTextNode(QVariant(this->switcherId).toString()));
   parent.appendChild(el);
    el = dom.createElement("on");
   el.appendChild(dom.createTextNode(QVariant(this->on).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Switcher::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("switcher_id")).length())
   {    this->switcherId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("on")).length())
   {    this->on = QVariant(list.at(0).toElement().text()).toBool();    }    

}