/***********************************************************************
 * Module:  Client.cpp
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
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
       this->clientId = DataBase::getQueryInt("client_id");
       this->adresseIp = DataBase::getQueryString("adresse_ip");       


 }