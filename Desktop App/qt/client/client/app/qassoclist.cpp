#include "qassoclist.h"

/*--------------------------------------------------------------------------------
  QAssocList
--------------------------------------------------------------------------------*/

/**
    @brief Retourne la valeur associée à une clé
    @param key Valeur de la clé
    @return Valeur associée à la clé
*/
QVariant QAssocList::getValue(const QString key)const{
    QAssocList::const_iterator i = this->find(key);
    if(i==this->end())
        return QVariant();
    return this->at(key);
}

/**
    @brief Retourne la valeur texte associée à une clé
    @param key Valeur de la clé
    @return Valeur texte associée à la clé
*/
QString QAssocList::getText(const QString key)const{
    QAssocList::const_iterator i = this->find(key);
    if(i==this->end())
        return QString();
    return this->at(key).toString();
}
