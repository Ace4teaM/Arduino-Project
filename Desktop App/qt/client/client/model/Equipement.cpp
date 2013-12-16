/***********************************************************************
 * Module:  Equipement.cpp
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
 * Purpose: Implementation of the class Equipement
 ***********************************************************************/

#include "Equipement.h"

void Equipement::bind(QSqlQuery & query){
       query.bindValue("equipement_id",QVariant(this->equipementId));
       query.bindValue("name",QVariant(this->name));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Equipement::bound(QSqlQuery & query){
       this->equipementId = DataBase::getQueryInt(query,"equipement_id");
       this->name = DataBase::getQueryString(query,"name");       

}