#include "result.h"

/** pointeur sur le dernier resultat */
Result* Result::plast = 0;

Result::Result(const QString& code)
{
    this->code = code;
    this->desc = QString("SUCCESS");
}
/*
Result::Result(const QString* code,const QString* desc){
    this->code = *code;
    this->desc = *desc;
}

Result::Result(const QString& code,const QString& desc){
    this->code = code;
    this->desc = desc;
}*/


Result::Result(const QString code,const QString desc){
    this->code = code;
    this->desc = desc;
}

Result::Result(const char* code,const char* desc){
    this->code = QString(code);
    this->desc = QString(desc);
}

const QString* Result::getCode()
{
    return &this->code;
}

const char* Result::getMsgA(){
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    return this->getMsg()->toAscii().data();
#else
    return this->getMsg()->toLatin1().data();
#endif
}

const char* Result::getDescA(){
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    return this->getDesc()->toAscii().data();
#else
    return this->getDesc()->toLatin1().data();
#endif
}

const QString* Result::getMsg()
{
    /*if(this->code <= (int)sizeof(Result::EM) && this->code >= 0)
        return Result::EM[this->code];*/
    return new QString("Erreur non définit");
}

const QString* Result::getDesc()
{
    return &this->desc;
}

bool Result::is_failed(){
    return (this->getCode()->compare(Result::OK,Qt::CaseInsensitive) == 0) ? true : false;
}

/*-------------------------------------------------------
  Static functions
-------------------------------------------------------*/

/** @brief Affiche le résultat dans la sortie standard */
void Result::print(Result* last){
    //deboguage...
    if(last->is_failed())
        printf("Result: (%s) %s\n",last->getCode()->toLatin1().data(),last->getMsgA());
    if(!last->getDesc()->isNull())
        printf("MESSAGE  : %s\n",last->getDescA());
    fflush(stdout);
}

/** @brief Assigne le dernier résultat */
bool Result::last(Result* last){
    //deboguage...
    if(last->is_failed()){
        Result::print(last);
    }
    //
    Result::plast=last;
    return (Result::plast->getCode() != 0 ? false : true);
}

/** @brief Test le dernier résultat */
bool Result::is_last_failed(){
    if(Result::plast == 0)
        return false;
    return (Result::plast->getCode() == 0 ? false : true);
}

/** @brief Obtient l'instance du dernier résultat */
Result* Result::getLast(){
    return Result::plast;
}

/*-------------------------------------------------------
  Liste des messages d'erreurs
-------------------------------------------------------*/

const QString Result::OK                      = "ERR_OK";
const QString Result::Failed                  = "ERR_FAILED";
const QString Result::SqlConnectionFailed     = "SQL_CONNECTION_FAILED";
const QString Result::CantOpenFile            = "CANT_OPEN_FILE";
const QString Result::SqlCreatQueryFailed     = "SQL_CREATE_REQUEST";
const QString Result::ApplicationInitFailed   = "APP_INIT_FAILED";
const QString Result::SqlEmptyResult          = "SQL_EMPTY_RESULT";
const QString Result::AppUnimplementedFeature = "APP_UNIMPLEMENTED_FEATURE";
const QString Result::CantSaveFile            = "CANT_SAVE_FILE";
const QString Result::CantEditXmlFile         = "CANT_EDIT_XML_FILE";
const QString Result::CantReadFile            = "CANT_READ_FILE";
