/***********************************************************************
 * Module:  Controleur.cpp
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
 * Purpose: Implementation of the class Controleur
 ***********************************************************************/

#include "Controleur.h"

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