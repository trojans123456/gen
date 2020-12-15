#include <QCoreApplication>
#include <QDebug>

#include "resource/t_thread.h"
#include "exception/t_exception.h"

class test_thread : public Thread
{
public:
     void run()
     {
         while(1)
         {
            qDebug() << "jfdksljf" ;
            Thread::threadSleep(1000);
         }
            qDebug() << "jfdkslj";
     }

private:

};

int main(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);

    try
    {
        throw TError("xxxx",20);
    }catch(TError &err)
    {
        qDebug() << err.getMessage() << err.getCode();
        qDebug() << TError::getStack();
    }

    test_thread tt;
    tt.Start();



    return a.exec();
}
