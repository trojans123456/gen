#ifndef T_SERIAL_H
#define T_SERIAL_H

#ifdef __linux__
#include <termios.h>
#endif

#include <QString>

enum CommStopBits
{
    COMM_STOPBIT_1 = 1,
    COMM_STOPBIT_2
};

enum CommParity
{
    COMM_PARITY_NONE,
    COMM_PARITY_ODD, /** 奇校验*/
    COMM_PARITY_EVEN,
    COMM_PARITY_MARK, /* 总为1 */
    COMM_PARITY_SPACE
};

enum CommDataBits
{
    COMM_DATA_5,
    COMM_DATA_6,
    COMM_DATA_7,
    COMM_DATA_8
};

enum CommFlowCtrl
{
    COMM_FLOW_OFF,
    COMM_FLOW_HARDWARE,
    COMM_FLOW_XONXOFF
};

enum CommBaudRate
{
    COMM_BAUD_50,
    COMM_BAUD_75,
    COMM_BAUD_110,
    COMM_BAUD_134,               //POSIX ONLY
    COMM_BAUD_150,               //POSIX ONLY
    COMM_BAUD_200,               //POSIX ONLY
    COMM_BAUD_300,
    COMM_BAUD_600,
    COMM_BAUD_1200,
    COMM_BAUD_1800,              //POSIX ONLY
    COMM_BAUD_2400,
    COMM_BAUD_4800,
    COMM_BAUD_9600,
    COMM_BAUD_14400,             //WINDOWS ONLY
    COMM_BAUD_19200,
    COMM_BAUD_38400,
    COMM_BAUD_56000,             //WINDOWS ONLY
    COMM_BAUD_57600,
    COMM_BAUD_76800,             //POSIX ONLY
    COMM_BAUD_115200,
    COMM_BAUD_128000,            //WINDOWS ONLY
    COMM_BAUD_256000             //WINDOWS ONLY
};

struct CommAttribute
{
    CommBaudRate baudrate;
    CommDataBits databits;
    CommParity   parity;
    CommStopBits  stopbits;
    CommFlowCtrl flowctrl;
    long timeout_ms;
};

class Serial
{
public:
    Serial();
    Serial(QString name);
    ~Serial();

    void setPortName(const QString &name);
    QString portName();

    void setBaudRate(CommBaudRate baudrate);
    CommBaudRate baudRate();

    void setDataBits(CommDataBits databits);
    CommDataBits dataBits();

    void setParity(CommParity parity);
    CommParity parity();

    void setStopBits(CommStopBits stopbits);
    CommStopBits stopBits();

    void setFlowControl(CommFlowCtrl flowctl);
    CommFlowCtrl flowControl();

    void setTimeout(long ms);

    void setDtr(bool set);
    void setRts(bool set);
    /**
    Mask        Line
    ------      ----
    LS_CTS      CTS
    LS_DSR      DSR
    LS_DCD      DCD
    LS_RI       RI
    LS_RTS      RTS (POSIX only)
    LS_DTR      DTR (POSIX only)
    LS_ST       Secondary TXD (POSIX only)
    LS_SR       Secondary RXD (POSIX only)
    */
    unsigned long lineStatus();

    bool isValid();
    bool open();
    void close();
    void flush();
    /** 返回阻塞在内核缓冲区中的字节数*/
    int size() const;

    int readData(char *data,int maxSize);
    int writeData(const char *data,int maxSize);

private:
    Serial(Serial &) {}
    Serial &operator=(Serial &) {return *this;}

private:
    QString mPort;
    CommAttribute mAttr;
    int mComfd;
    struct termios mTermios;
};

#endif
