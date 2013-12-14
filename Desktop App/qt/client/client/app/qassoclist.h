#ifndef QASSOCLIST_H
#define QASSOCLIST_H

#include <QString>
#include <QVariant>
#include <vector>

class QAssocList : public std::map<QString,QVariant>
{
public:
    //retourne la valeur associée à une clé
    QVariant getValue(const QString key)const;
    //retourne la valeur texte associée à une clé
    QString getText(const QString key)const;
};

#endif // QASSOCLIST_H
