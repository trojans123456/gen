#ifndef T_SOCKET_H
#define T_SOCKET_H

#include <QString>

class Socket
{
public:
    enum SocketType
    {
        SOCKET_TYPE_NONE = -1,
        SOCKET_TYPE_TCP = 0,
        SOCKET_TYPE_UDP,
        SOCKET_TYPE_CAN,
        SOCKET_TYPE_RAW,
        SOCKET_TYPE_NETLINK
    };


    Socket(SocketType type);
    virtual ~Socket();

    unsigned short localPort();
    QString localAddress();

    bool sockOpen();
    void sockClose();
    void sockFlush();
    virtual bool sockConnect() { return false;}

    /* 判断fd是否有效*/
    bool isValid();
    /* 获取文件描述符*/
    int getSockfd();

    bool setNonBlocking();
    static bool setNonBlocking(int fd);
    /** ip地址复用*/
    bool setSockReused();

    unsigned short remotePort();
    QString remoteAddress();



private:
    int mSockFd;
    SocketType mSockType;
};


#endif
