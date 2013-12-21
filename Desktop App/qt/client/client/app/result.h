#ifndef RESULT_H
#define RESULT_H

#include <QString>
#include <stdio.h>

//Result macro
#define QRESULT(c)          Result::last(new Result(c))
#define QRESULT_DESC(c,t)   Result::last(new Result(c,t))
#define IS_FAILED()         Result::is_last_failed()
#define QRESULT_OK()        Result::last(new Result("ERR_OK"))

//Stdout macro
#ifdef _DEBUG
#define PRINT(m)            puts(m);\
                            fflush(stdout)
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#define QPRINT(m)           puts((m).toAscii().data());\
                            fflush(stdout)
#define QPRINT_PTR(m)       puts((m)->toAscii().data());\
                            fflush(stdout)
#else
#define QPRINT(m)           puts((m).toLocal8Bit().data());\
                            fflush(stdout)
#define QPRINT_PTR(m)       puts((m)->toLocal8Bit().data());\
                            fflush(stdout)
#endif
#else
#define PRINT(m)            ;
#define QPRINT(m)           ;
#define QPRINT_PTR(m)       ;
#endif

class Result
{
public:
    Result(const QString& code);
   /* Result(const QString* code,const QString* desc);
    Result(const QString& code,const QString& desc);*/
    Result(const QString code,const QString desc);
    Result(const char* code,const char* desc);

    //last
    static bool last(Result* last);
    static bool is_last_failed();
    static Result* getLast();

    //deboguage
    static void print(Result* last);

    //current
    const QString* getCode();
    bool is_failed();
    const QString* getMsg();
    const QString* getDesc();
    const char* getMsgA();
    const char* getDescA();

    /** @brief Codes d'erreurs de l'application */
    static const QString OK;
    static const QString Failed;
    static const QString SqlConnectionFailed;
    static const QString CantOpenFile;
    static const QString SqlCreatQueryFailed;
    static const QString ApplicationInitFailed;
    static const QString SqlEmptyResult;
    static const QString AppUnimplementedFeature;
    static const QString CantSaveFile;
    static const QString CantReadFile;
    static const QString CantEditXmlFile;
private:
    QString code;
    QString desc;
    static Result* plast;
};

#endif // RESULT_H
