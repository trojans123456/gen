#ifndef T_EXCEPTION_H
#define T_EXCEPTION_H

#include <QString>


class TError
{
public:
    TError():mMsg(""),mCode(-1) {}
    TError(QString msg,int code):mMsg(msg),mCode(code) {}
    TError(QString msg):mMsg(msg),mCode(-1) {}

    QString &getMessage() {return mMsg;}
    int &getCode() {return mCode;}

    static QString getStack();
    static QString lastError();

private:
    QString mMsg;
    int mCode;
};


#endif
