/***********************************************************************
 * Module:  Pin.cpp
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:57:56
 * Purpose: Implementation of the class Pin
 ***********************************************************************/

#include "Pin.h"

void Pin::bind(QSqlQuery & query){
       query.bindValue("pin_id",QVariant(this->pinId));
       query.bindValue("pin_type",QVariant(this->pinType));
       query.bindValue("pin_num",QVariant(this->pinNum));       

 }

/*
   @brief Get data form current SQL query
   @param query Query instance
*/
void Pin::bound(QSqlQuery & query){
       this->pinId = DataBase::getQueryInt(query,"pin_id");
       this->pinType = DataBase::getQueryString(query,"pin_type");
       this->pinNum = DataBase::getQueryInt(query,"pin_num");       

}