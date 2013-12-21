#include "database.h"

DataBase::DataBase(const QString & connectionName)
{
    //Ouverture de la base de données MySQL
    this->db = QSqlDatabase::addDatabase("QMYSQL",connectionName);
}

/**
    @brief Ouvre la connexion avec les paramétres de la configuration locale
    @return true en cas de succès, false en cas d'échec
*/
bool DataBase::open(const QString& configFileName)
{
/*    this->db.setHostName(this->configParams["host_name"]->getValue());
    this->db.setDatabaseName(this->configParams["database_name"]->getValue());
    this->db.setUserName(this->configParams["user_name"]->getValue());
    this->db.setPassword(this->configParams["password"]->getValue());
*/
    //parametres de configuration
    ConfigParamList list;
    Configurable::set(list,"host_name","localhost");
    Configurable::set(list,"database_name","quertech");
    Configurable::set(list,"user_name","root");
    Configurable::set(list,"password","");

    //charge la configuration en cours
    ConfigXmlFile::load(configFileName,this,list);

    return this->configUpdate(list);

}

/**
    @brief Ouvre la connexion avec des paramétres sécifiques
    @remarks Les paramètres de connexion ne sont pas ajoutés à la configuration
    @return true en cas de succès, false en cas d'échec
*/
bool DataBase::open(const QString& hostname,const QString& database_name,const QString& user_name,const QString& password)
{
    this->db.setHostName(hostname);
    this->db.setDatabaseName(database_name);
    this->db.setUserName(user_name);
    this->db.setPassword(password);

    if(!this->db.open())
        return QRESULT_DESC(Result::SqlConnectionFailed,this->db.lastError().text());

    return QRESULT_OK();
}

//ferme la connexion
void DataBase::close(){
    this->db.close();
}

//prepare une requete
QSqlQuery* DataBase::query(const QString query_str){
    QSqlQuery* query = new QSqlQuery();
    // Obtient l'instance
    query->clear();
    if(!query->prepare(query_str))
    {
        QRESULT_DESC(Result::SqlCreatQueryFailed, query->lastError().text());
        return 0;
    }

    return query;
}

/*---------------------------------------------------------------------------
   Recuperation des champs
---------------------------------------------------------------------------*/

//
QString DataBase::getQueryString(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryString not found for ")+fieldName);
#endif
    return query.value(index).toString();
}

//
int DataBase::getQueryInt(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryString not found for ")+fieldName);
#endif
    return query.value(index).toInt();
}

//
float DataBase::getQueryFloat(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryString not found for ")+fieldName);
#endif
    return query.value(index).toFloat();
}

//
QDate DataBase::getQueryDate(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryString not found for ")+fieldName);
#endif
    QString value = query.value(index).toString();
    QDate date =  QDate::fromString(value, "yyyy-MM-dd");

    /*Result::print(new Result(0,(date.isValid() ? "true" : "false")));
    Result::print(new Result(0,QString::number(date.day())));
    Result::print(new Result(0,QString::number(date.month())));
    Result::print(new Result(0,QString::number(date.year())));
    Result::print(new Result(0,date.toString(Qt::ISODate)));*/
    return date;
}

//
QTime DataBase::getQueryTime(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryTime not found for ")+fieldName);
#endif
    QTime date = query.value(index).toTime();

    return date;
}

//
QDelay DataBase::getQueryDelay(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryDelay not found for ")+fieldName);
#endif
    return QDelay(query.value(index).toInt());
}

//
QDateTime DataBase::getQueryDateTime(QSqlQuery& query, const QString& fieldName){
    int index = query.record().indexOf(fieldName);
#ifdef _DEBUG
    if(index<0)
        QPRINT(QString("getQueryString not found for ")+fieldName);
#endif
    QDateTime date = query.value(index).toDateTime();

    return date;
}

/*---------------------------------------------------------------------------
    Convertions des champs en texte (optimisée pour MySQL)
---------------------------------------------------------------------------*/

QString DataBase::fieldToString(const QDate& d){
    return d.toString("yyyy-MM-dd");
}

QString DataBase::fieldToString(const QDateTime& d){
    return d.toString("yyyy-MM-dd hh:mm:ss");
}

QString DataBase::fieldToString(const int& v){
    return QString::number(v);
}

QString DataBase::fieldToString(const float& v){
    return QString::number(v);
}

QString DataBase::fieldToString(const double& v){
    return QString::number(v);
}

QString DataBase::fieldToString(const QTime& d){
    return d.toString("hh:mm:ss");
}

QString DataBase::fieldToDelay(const QDelay& d){
    return d.toString();
}

/*---------------------------------------------------------------------------
    Configuration
---------------------------------------------------------------------------*/

const QString DataBase::getConfigTitle(){
    return "Base de données";
}

const QString DataBase::getConfigName(){
    return "database";
}

bool DataBase::configUpdate(ConfigParamList& list){

    if(this->db.isOpen())
        this->db.close();

    QPRINT("configUpdate = "+Configurable::get(list,"host_name"));

    this->db.setHostName(Configurable::get(list,"host_name"));
    this->db.setDatabaseName(Configurable::get(list,"database_name"));
    this->db.setUserName(Configurable::get(list,"user_name"));
    this->db.setPassword(Configurable::get(list,"password"));

    if(!this->db.open())
        return QRESULT_DESC(Result::SqlConnectionFailed,this->db.lastError().text());

    return QRESULT_OK();
}

bool DataBase::configRead(ConfigParamList& list){

    Configurable::set(list,"host_name",this->db.hostName());
    Configurable::set(list,"database_name",this->db.databaseName());
    Configurable::set(list,"user_name",this->db.userName());
    Configurable::set(list,"password",this->db.password());
    return true;
}

/*---------------------------------------------------------------------------
    Heritée
---------------------------------------------------------------------------*/

bool DataBase::isOpen() const{
    return this->db.isOpen();
}

void DataBase::setDatabaseName( const QString & name ){
    this->db.setDatabaseName(name);
}
