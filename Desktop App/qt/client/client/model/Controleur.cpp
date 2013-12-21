/***********************************************************************
 * Module:  Controleur.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Controleur
 ***********************************************************************/

#include "Controleur.h"

/*
   @brief Put data current SQL query
   @param query Query instance
*/
void Controleur::bind(QSqlQuery & query){
       query.bindValue("controleur_id",QVariant(this->controleurId));
       query.bindValue("adresse_ip",QVariant(this->adresseIp));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Controleur::bound(QSqlQuery & query){
       this->controleurId = DataBase::getQueryInt(query,"controleur_id");
       this->adresseIp = DataBase::getQueryString(query,"adresse_ip");       

}

/*
   @brief Put data to DomElement
   @param dom QDomElement Parent Element
*/
void Controleur::bindXML(QDomElement & parent){
   QDomDocument dom = parent.ownerDocument();
   QDomElement el;
    el = dom.createElement("controleur_id");
   el.appendChild(dom.createTextNode(QVariant(this->controleurId).toString()));
   parent.appendChild(el);
    el = dom.createElement("adresse_ip");
   el.appendChild(dom.createTextNode(QVariant(this->adresseIp).toString()));
   parent.appendChild(el);    

 }

/*
   @brief Get data form DomElement
   @param dom QDomElement Parent Element
*/
void Controleur::boundXML(QDomElement & parent){
   QDomNodeList list;
   if((list = parent.elementsByTagName("controleur_id")).length())
   {    this->controleurId = list.at(0).toElement().text().toInt();    }
   if((list = parent.elementsByTagName("adresse_ip")).length())
   {    this->adresseIp = list.at(0).toElement().text();    }    

}