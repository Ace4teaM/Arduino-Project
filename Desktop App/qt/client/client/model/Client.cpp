/***********************************************************************
 * Module:  Client.cpp
 * Author:  developpement
 * Modified: mercredi 18 décembre 2013 07:44:09
 * Purpose: Implementation of the class Client
 ***********************************************************************/

#include "Client.h"

void Client::bind(QSqlQuery & query){
       query.bindValue("client_id",QVariant(this->clientId));
       query.bindValue("adresse_ip",QVariant(this->adresseIp));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Client::bound(QSqlQuery & query){
       this->clientId = DataBase::getQueryInt(query,"client_id");
       this->adresseIp = DataBase::getQueryString(query,"adresse_ip");       

}