/***********************************************************************
 * Module:  Equipement.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Equipement
 ***********************************************************************/

#include "Equipement.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Equipement::bind(QSqlQuery & query){
       query.bindValue("equipement_id",QVariant(this->equipementId));
       query.bindValue("name",QVariant(this->name));
       query.bindValue("type",QVariant(this->type));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Equipement::bound(QSqlQuery & query){
       this->equipementId = DataBase::getQueryInt(query,"equipement_id");
       this->name = DataBase::getQueryString(query,"name");
       this->type = DataBase::getQueryString(query,"type");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Equipement::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("equipement_id");
   el.appendChild(dom.createTextNode(QVariant(this->equipementId).toString()));
   parent.appendChild(el);
    el = dom.createElement("name");
   el.appendChild(dom.createTextNode(QVariant(this->name).toString()));
   parent.appendChild(el);
    el = dom.createElement("type");
   el.appendChild(dom.createTextNode(QVariant(this->type).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Equipement::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("equipement_id")).length())
   {    this->equipementId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("name")).length())
   {    this->name = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("type")).length())
   {    this->type = list.at(0).toElement().text();    }    

}