#include <QCoreApplication>
#include <QDebug>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "event/t_event.h"
#include "resource/t_thread.h"
#include "exception/t_exception.h"

int time_proc(long long id,void *priv)
{
    printf("jslkjflkds\n");
    fflush(stdout);
    return 1000;
}

void file_proc(int fd,void *priv,int mask)
{
    int xx = *(int *)priv;
    printf("xx = %d fd = %d mask = %d\n",xx,fd,mask);
    fflush(stdout);

    if(fd == xx)
    {
        printf("equal ....\n");
        fflush(stdout);

        write(fd,"test...",strlen("test..."));
        sleep(1);
    }
}


class test_thread : public Thread
{
public:
     void run()
     {
         EventLoop *loop = new EventLoop();
         if(!loop)
             qDebug() <<"jsflksjd";


         int fd = open("xx.log",O_RDWR);

         loop->evCreateTimeEvent(1000,time_proc,NULL,NULL);
         loop->evCreateFileEvent(fd,EVENT_WRITABLE,file_proc,(void*)&fd);
         loop->evStart();


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
