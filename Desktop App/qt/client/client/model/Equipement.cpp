/***********************************************************************
 * Module:  Equipement.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Equipement
 ***********************************************************************/

#include "Equipement.h"

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