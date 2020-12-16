#include <stdio.h>
#ifdef __linux__
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/inet.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif
#include "socket/t_socket.h"

Socket::Socket(SocketType type)
    :mSockFd(-1)
    ,mSockType(SOCKET_TYPE_NONE)
{

}

Socket::~Socket()
{
    if(isValid())
        sockClose();
}

unsigned short Socket::localPort()
{

}

QString Socket::localAddress()
{

}

bool Socket::sockOpen()
{

}

void Socket::sockClose()
{

}

void Socket::sockFlush()
{

}



/* 判断fd是否有效*/
bool Socket::isValid()
{

}

/* 获取文件描述符*/
int Socket::getSockfd()
{

}

bool Socket::setNonBlocking()
{
    if(!isValid())
        return false;
    if(fcntl(mSockFd,F_SETFL,O_NONBLOCK) == -1)
        return false;
    return true;
}

bool Socket::setNonBlocking(int fd)
{

}

/** ip地址复用*/
bool Socket::setSockReused()
{

}

unsigned short Socket::remotePort()
{

}

QString Socket::remoteAddress()
{

}
