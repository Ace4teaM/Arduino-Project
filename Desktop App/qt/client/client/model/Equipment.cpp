/***********************************************************************
 * Module:  Equipment.cpp
 * Author:  developpement
 * Modified: dimanche 22 décembre 2013 09:19:05
 * Purpose: Implementation of the class Equipment
 ***********************************************************************/

#include "Equipment.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Equipment::bind(QSqlQuery & query){
       query.bindValue("equipment_id",QVariant(this->equipmentId));
       query.bindValue("name",QVariant(this->name));
       query.bindValue("type",QVariant(this->type));
       query.bindValue("pos_x",QVariant(this->posX));
       query.bindValue("pos_y",QVariant(this->posY));
       query.bindValue("pos_z",QVariant(this->posZ));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Equipment::bound(QSqlQuery & query){
       this->equipmentId = DataBase::getQueryInt(query,"equipment_id");
       this->name = DataBase::getQueryString(query,"name");
       this->type = DataBase::getQueryString(query,"type");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Equipment::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("equipment_id");
   el.appendChild(dom.createTextNode(QVariant(this->equipmentId).toString()));
   parent.appendChild(el);
    el = dom.createElement("name");
   el.appendChild(dom.createTextNode(QVariant(this->name).toString()));
   parent.appendChild(el);
    el = dom.createElement("type");
   el.appendChild(dom.createTextNode(QVariant(this->type).toString()));
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
void Equipment::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("equipment_id")).length())
   {    this->equipmentId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("name")).length())
   {    this->name = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("type")).length())
   {    this->type = list.at(0).toElement().text();    }
   if((list = parent.elementsByTagName("pos_x")).length())
   {    }
   if((list = parent.elementsByTagName("pos_y")).length())
   {    }
   if((list = parent.elementsByTagName("pos_z")).length())
   {    }    

}