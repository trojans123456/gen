#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef __linux__
#include <sys/time.h>
#include <errno.h>
#include <sys/ioctl.h>
#endif
#include "serial/t_serial.h"

Serial::Serial()
    :mPort("")
    ,mComfd(-1)
{
    mAttr.baudrate = COMM_BAUD_115200;
    mAttr.databits = COMM_DATA_8;
    mAttr.parity = COMM_PARITY_NONE;
    mAttr.stopbits = COMM_STOPBIT_1;
    mAttr.flowctrl = COMM_FLOW_OFF;
    mAttr.timeout_ms = 30;/** 超时帧 判断*/
}

Serial::Serial(QString name)
    :mPort("")
    ,mComfd(-1)
{
    setPortName(name);

    mAttr.baudrate = COMM_BAUD_115200;
    mAttr.databits = COMM_DATA_8;
    mAttr.parity = COMM_PARITY_NONE;
    mAttr.stopbits = COMM_STOPBIT_1;
    mAttr.flowctrl = COMM_FLOW_OFF;
    mAttr.timeout_ms = 30;/** 超时帧 判断*/
}
Serial::~Serial()
{
    close();
}

void Serial::setPortName(const QString &name)
{
    mPort = name;
}
QString Serial::portName()
{
    return mPort;
}

void Serial::setBaudRate(CommBaudRate baudrate)
{
    mAttr.baudrate = baudrate;

    switch (mAttr.baudrate)
    {
    case COMM_BAUD_50:
        cfsetispeed(&mTermios, B50);
        cfsetospeed(&mTermios, B50);
        break;
    case COMM_BAUD_75:
        cfsetispeed(&mTermios, B75);
        cfsetospeed(&mTermios, B75);
        break;
    case COMM_BAUD_110:
        cfsetispeed(&mTermios, B110);
        cfsetospeed(&mTermios, B110);
        break;
    case COMM_BAUD_134:
        cfsetispeed(&mTermios, B134);
        cfsetospeed(&mTermios, B134);
        break;
    case COMM_BAUD_150:
        cfsetispeed(&mTermios, B150);
        cfsetospeed(&mTermios, B150);
        break;
    case COMM_BAUD_200:
        cfsetispeed(&mTermios, B200);
        cfsetospeed(&mTermios, B200);
        break;
    case COMM_BAUD_300:
        cfsetispeed(&mTermios, B300);
        cfsetospeed(&mTermios, B300);
        break;
    case COMM_BAUD_600:
        cfsetispeed(&mTermios, B600);
        cfsetospeed(&mTermios, B600);
        break;
    case COMM_BAUD_1200:
        cfsetispeed(&mTermios, B1200);
        cfsetospeed(&mTermios, B1200);
        break;
    case COMM_BAUD_1800:
        cfsetispeed(&mTermios, B1800);
        cfsetospeed(&mTermios, B1800);
        break;
    case COMM_BAUD_2400:
        cfsetispeed(&mTermios, B2400);
        cfsetospeed(&mTermios, B2400);
        break;
    case COMM_BAUD_4800:
        cfsetispeed(&mTermios, B4800);
        cfsetospeed(&mTermios, B4800);
        break;
    case COMM_BAUD_9600:
        cfsetispeed(&mTermios, B9600);
        cfsetospeed(&mTermios, B9600);
        break;
    case COMM_BAUD_19200:
        cfsetispeed(&mTermios, B19200);
        cfsetospeed(&mTermios, B19200);
        break;
    case COMM_BAUD_38400:
        cfsetispeed(&mTermios, B38400);
        cfsetospeed(&mTermios, B38400);
        break;
    case COMM_BAUD_57600:
        cfsetispeed(&mTermios, B57600);
        cfsetospeed(&mTermios, B57600);
        break;
    case COMM_BAUD_115200:
        cfsetispeed(&mTermios, B115200);
        cfsetospeed(&mTermios, B115200);
        break;
    case COMM_BAUD_128000:
        cfsetispeed(&mTermios, B230400);
        cfsetospeed(&mTermios, B230400);
        break;
    case COMM_BAUD_256000:
        cfsetispeed(&mTermios, B460800);
        cfsetospeed(&mTermios, B460800);
        break;
    default:
        break;
    }
    tcsetattr(mComfd, TCSANOW, &mTermios);
}
CommBaudRate Serial::baudRate()
{
    return mAttr.baudrate;
}

void Serial::setDataBits(CommDataBits databits)
{
    mAttr.databits = databits;

    mTermios.c_cflag &= ~CSIZE;
    switch (mAttr.databits)
    {
    case COMM_DATA_5:
        mTermios.c_cflag |= CS5;
        break;
    case COMM_DATA_6:
        mTermios.c_cflag |= CS6;
        break;
    case COMM_DATA_7:
        mTermios.c_cflag |= CS7;
        break;
    case COMM_DATA_8:
        mTermios.c_cflag |= CS8;
        break;
    default:
        break;
    }
    tcsetattr(mComfd, TCSANOW, &mTermios);
}
CommDataBits Serial::dataBits()
{
    return mAttr.databits;
}

void Serial::setParity(CommParity parity)
{
    mAttr.parity = parity;

    switch (mAttr.parity)
    {
    case COMM_PARITY_NONE:		    /* none			*/
        mTermios.c_cflag &= ~PARENB;	/* disable parity	*/
        mTermios.c_iflag &= ~INPCK;	/* disable parity check	*/
        break;
    case COMM_PARITY_ODD:		/* odd			*/
        mTermios.c_cflag |= PARENB;	/* enable parity	*/
        mTermios.c_cflag |= PARODD;	/* odd			*/
        mTermios.c_iflag |= INPCK;	/* enable parity check	*/
        break;
    case COMM_PARITY_EVEN:		/* even			*/
        mTermios.c_cflag |= PARENB;	/* enable parity	*/
        mTermios.c_cflag &= ~PARODD;	/* even			*/
        mTermios.c_iflag |= INPCK;	/* enable parity check	*/
    default:
        break;
    }
    tcsetattr(mComfd, TCSANOW, &mTermios);
}
CommParity Serial::parity()
{
    return mAttr.parity;
}

void Serial::setStopBits(CommStopBits stopbits)
{
    mAttr.stopbits = stopbits;

    mTermios.c_cflag &= ~CSTOPB;
    switch (mAttr.stopbits)
    {
    case COMM_STOPBIT_1:
        mTermios.c_cflag &= ~CSTOPB;
        break;
        /*		case COMM_STOPBIT_1_5:
                break;
    */
    case COMM_STOPBIT_2:
        mTermios.c_cflag |= CSTOPB;
        break;
    default:
        break;
    }
    tcsetattr(mComfd, TCSANOW, &mTermios);
}
CommStopBits Serial::stopBits()
{
    return mAttr.stopbits;
}

void Serial::setFlowControl(CommFlowCtrl flowctl)
{
    mAttr.flowctrl = flowctl;
}
CommFlowCtrl Serial::flowControl()
{
    return mAttr.flowctrl;
}

void Serial::setTimeout(long ms)
{
    mAttr.timeout_ms = ms;

    if(isValid())
    {
        tcgetattr(mComfd,&mTermios);
        mTermios.c_cc[VTIME] = ms / 100;
        tcsetattr(mComfd,TCSAFLUSH,&mTermios);
    }
}

void Serial::setDtr(bool set)
{
    if(isValid())
    {
        int status;
        ioctl(mComfd,TIOCMGET,&status);
        if(set)
        {
            status |= TIOCM_DTR;
        }
        else {
            status &= ~TIOCM_DTR;
        }
        ioctl(mComfd,TIOCMSET,&status);
    }
}

void Serial::setRts(bool set)
{
    if(isValid())
    {
        int status;
        ioctl(mComfd,TIOCMGET,&status);
        if(set)
        {
            status |= TIOCM_RTS;
        }
        else {
            status &= ~TIOCM_RTS;
        }
        ioctl(mComfd,TIOCMSET,&status);
    }
}

unsigned long Serial::lineStatus()
{
    #if 0
    unsigned long Status=0, Temp=0;

    if (isValid()) {
        ioctl(mComfd, TIOCMGET, &Temp);
        if (Temp&TIOCM_CTS) {
            Status|=LS_CTS;
        }
        if (Temp&TIOCM_DSR) {
            Status|=LS_DSR;
        }
        if (Temp&TIOCM_RI) {
            Status|=LS_RI;
        }
        if (Temp&TIOCM_CD) {
            Status|=LS_DCD;
        }
        if (Temp&TIOCM_DTR) {
            Status|=LS_DTR;
        }
        if (Temp&TIOCM_RTS) {
            Status|=LS_RTS;
        }
        if (Temp&TIOCM_ST) {
            Status|=LS_ST;
        }
        if (Temp&TIOCM_SR) {
            Status|=LS_SR;
        }
    }
#endif
    return 0;
}

bool Serial::isValid()
{
    return (mComfd > 0) ? true : false;
}
bool Serial::open()
{
    if(isValid())
        return false;
    printf("%s \n",mPort.toUtf8().data());
    fflush(stdout);
    mComfd = ::open(mPort.toUtf8().data(),O_RDWR | O_NOCTTY | O_NDELAY);
    if(mComfd < 0)
        return false;

    tcgetattr(mComfd,&mTermios);
    cfmakeraw(&mTermios); /* set raw mode */
    mTermios.c_iflag = IGNBRK; /* 忽略break */

    mTermios.c_cc[VTIME] = 0;
    mTermios.c_cc[VMIN] = 1;

    tcsetattr(mComfd,TCSANOW,&mTermios);

    return true;
}
void Serial::close()
{
    if(isValid())
    {
        ::close(mComfd);
    }
}
void Serial::flush()
{
    if(isValid())
    {
        tcflush(mComfd,TCOFLUSH); /* flush tx */
        tcflush(mComfd,TCIFLUSH);
    }
}

int Serial::size() const
{
    int bytes = 0;
    if(ioctl(mComfd,FIONREAD,&bytes) < 0)
        bytes = 0;
    return bytes;
}

int Serial::readData(char *data, int maxSize)
{
    int cur = 0,read_len = 0;

     while(cur < maxSize)
     {
         read_len = read(mComfd,data + cur,maxSize - cur);
         if(read_len < 0)
         {
             if(errno == EINTR ||
                errno == EAGAIN)
             {
                 continue;
             }
             return -1;
         }
         if(read_len == 0)
             break;

         cur += read_len;
     }
     return cur;
}

int Serial::writeData(const char *data, int maxSize)
{
    int cur = 0;
    int written = 0;
    while(cur < maxSize)
    {
        written = write(mComfd,data + cur,maxSize - cur);
        if(written < 0)
        {
            /*被中断 或资源不足*/
            if(errno == EINTR ||
                    errno == EAGAIN)
            {
                continue;
            }
            return -1;
        }
        if(written == 0)
            break;

        cur += written;
    }
    return cur;
}
