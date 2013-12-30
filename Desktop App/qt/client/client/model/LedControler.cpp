/***********************************************************************
 * Module:  LedControler.cpp
 * Author:  developpement
 * Modified: lundi 30 décembre 2013 18:05:09
 * Purpose: Implementation of the class LedControler
 ***********************************************************************/

#include "LedControler.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void LedControler::bind(QSqlQuery & query){
       query.bindValue("led_controler_id",QVariant(this->ledControlerId));
       query.bindValue("color_mode",QVariant(this->colorMode));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void LedControler::bound(QSqlQuery & query){
       this->ledControlerId = DataBase::getQueryInt(query,"led_controler_id");
       this->colorMode = DataBase::getQueryInt(query,"color_mode");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void LedControler::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("led_controler_id");
   el.appendChild(dom.createTextNode(QVariant(this->ledControlerId).toString()));
   parent.appendChild(el);
    el = dom.createElement("color_mode");
   el.appendChild(dom.createTextNode(QVariant(this->colorMode).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void LedControler::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("led_controler_id")).length())
   {    this->ledControlerId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("color_mode")).length())
   {    this->colorMode = list.at(0).toElement().text().toInt();    }    

}