#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QtSql>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include "qdelay.h"
#include "result.h"
#include "configurable.h"

class DataBase : public Configurable
{
public:
    DataBase(const QString & connectionName = QLatin1String( QSqlDatabase::defaultConnection ));
    bool open(const QString& configFileName);
    bool open(const QString& hostname,const QString& database_name,const QString& user_name,const QString& password);
    bool isOpen()const;
    void setDatabaseName( const QString & name );
    QSqlQuery* query(const QString query);
    void close();
    //recuperation des champs
    static QDate getQueryDate(QSqlQuery& query, const QString& fieldName);
    static QString getQueryString(QSqlQuery& query, const QString& fieldName);
    static int getQueryInt(QSqlQuery& query, const QString& fieldName);
    static float getQueryFloat(QSqlQuery& query, const QString& fieldName);
    static QTime getQueryTime(QSqlQuery& query, const QString& fieldName);
    static QDateTime getQueryDateTime(QSqlQuery& query, const QString& fieldName);
    static QDelay getQueryDelay(QSqlQuery& query, const QString& fieldName);
    //convertions des champs en texte (optimisé pour MySQL)
    static QString fieldToString(const QDate& d);
    static QString fieldToString(const QDateTime& d);
    static QString fieldToString(const QTime& d);
    static QString fieldToString(const int& v);
    static QString fieldToString(const float& v);
    static QString fieldToString(const double& v);
    static QString fieldToDelay(const QDelay& v);
    //Configurable
    const QString getConfigTitle();
    const QString getConfigName();
    bool configUpdate(ConfigParamList& list);
    bool configRead(ConfigParamList& list);
private:
    // connexion à  la base de données
    QSqlDatabase db;
};

#endif // DATABASE_H
