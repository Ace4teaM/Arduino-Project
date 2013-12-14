#ifndef RESULT_H
#define RESULT_H

#include <QString>
#include <stdio.h>

//Result macro
#define RESULT(c)           Result::last(new Result(c))
#define RESULT_DESC(c,t)    Result::last(new Result(c,t))
#define IS_FAILED(c)        Result::is_last_failed()
#define RESULT_OK           Result::last(new Result(Result::EC_OK))

//Stdout macro
#ifdef _DEBUG
#define PRINT(m)            puts(m);\
                            fflush(stdout)
#define QPRINT(m)           puts((m).toAscii().data());\
                            fflush(stdout)
#define QPRINT_PTR(m)       puts((m)->toAscii().data());\
                            fflush(stdout)
#else
#define PRINT(m)            ;
#define QPRINT(m)           ;
#define QPRINT_PTR(m)       ;
#endif

class Result
{
public:
    Result(int code);
    Result(int code,const QString* desc);
    Result(int code,const QString& desc);
    Result(int code,const char* desc);

    //last
    static bool last(Result* last);
    static bool is_last_failed();
    static Result* getLast();

    //deboguage
    static void print(Result* last);

    //current
    int getCode();
    bool is_failed();
    const QString* getMsg();
    const QString* getDesc();
    const char* getMsgA();
    const char* getDescA();

    /** @brief Codes d'erreurs de l'application */
    enum EC {
        EC_OK,
        EC_DATA_BASE_CONNECT,
        EC_OPEN_CFG_FILE,
        EC_SQL_QUERY,
        EC_APP_INIT,
        EC_SQL_NO_RESULT,
        EC_FEATURE_NOT_IMPLEMENTED,
        EC_XML_FILE_EDIT,
        EC_ACTION
    };
    /** @brief Textes des codes d'erreurs */
    static const QString* EM[];
private:
    int code;
    const QString* desc;
    static Result* plast;
};

#endif // RESULT_H
