#include <QCoreApplication>
#include <QDebug>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "event/t_event.h"
#include "resource/t_thread.h"
#include "exception/t_exception.h"
#include "serial/t_serial.h"

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



int xx_main(int argc,char *argv[])
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

    Serial *serial = new Serial("/dev/ttyO2");

    bool ret = serial->open();
    if(!ret)
    {
        qDebug() << "open failed\n";
    }
    serial->setBaudRate(COMM_BAUD_115200);
    serial->setDataBits(COMM_DATA_8);
    serial->setParity(COMM_PARITY_NONE);
    serial->setStopBits(COMM_STOPBIT_1);

    while(1)
    {
        serial->writeData("fjslkj",strlen("fjslkj"));
        sleep(1);
    }

    return a.exec();
}

int main(int argc,char *argv[])
{
    QString str = argv[1];
    Serial *serial = new Serial();
    serial->setPortName(str);
    bool ret = serial->open();
    if(!ret)
    {
        qDebug() << "open failed\n";
    }
    serial->setBaudRate(COMM_BAUD_115200);
    serial->setDataBits(COMM_DATA_8);
    serial->setParity(COMM_PARITY_NONE);
    serial->setStopBits(COMM_STOPBIT_1);

    while(1)
    {
        serial->writeData("fjslkj",strlen("fjslkj"));
        sleep(1);
    }
}
