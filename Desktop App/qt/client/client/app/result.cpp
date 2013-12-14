#include "result.h"

const QString* Result::EM[]={
    new QString("Aucune erreur") ,
    new QString("Connexion à la base de données impossible") ,
    new QString("Impossible d'ouvrir le fichier de configuration"),
    new QString("Impossible de créer la requête SQL"),
    new QString("Echec lors de l'initialisation de l'application"),
    new QString("La requête SQL ne retourne pas de résultat"),
    new QString("Fonctionnalité non implentée"),
    new QString("Impossible d'éditer le fichier XML"),
    new QString("Action impossible")
};

/** pointeur sur le dernier resultat */
Result* Result::plast = 0;

Result::Result(int code)
{
    this->code = code;
    this->desc = new QString("N/A");
}

Result::Result(int code,const QString* desc){
    this->code = code;
    this->desc = desc;
}

Result::Result(int code,const QString& desc){
    this->code = code;
    this->desc = new QString(desc);
}

Result::Result(int code,const char* desc){
    this->code = code;
    this->desc = new QString(desc);
}

int Result::getCode()
{
    return this->code;
}

const char* Result::getMsgA(){
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    return this->getMsg()->toAscii().data();
#else
    return this->getMsg()->toLocal8Bit().data();
#endif
}

const char* Result::getDescA(){
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    return this->getDesc()->toAscii().data();
#else
    return this->getDesc()->toLocal8Bit().data();
#endif
}

const QString* Result::getMsg()
{
    if(this->code <= (int)sizeof(Result::EM) && this->code >= 0)
        return Result::EM[this->code];
    return new QString("Erreur non définit");
}

const QString* Result::getDesc()
{
    return this->desc;
}

bool Result::is_failed(){
    return (this->getCode() == 0 ? false : true);
}

/*-------------------------------------------------------
  Static functions
-------------------------------------------------------*/

/** @brief Affiche le résultat dans la sortie standard */
void Result::print(Result* last){
    //deboguage...
    if(last->is_failed())
        printf("ERR_TRACE: (%d) %s\n",last->getCode(),last->getMsgA());
    if(last->getDesc() != 0)
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

/** @ brief Obtient l'instance du dernier résultat */
Result* Result::getLast(){
    return Result::plast;
}

