#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QThread>
#include "zlgcan.h"

struct VCI_CAN_OBJ
{
    int ID;
    int RemoteFlag;
    int ExternFlag;
    int DLC;
    QString Data;
};

class ReceiveThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveThread(QObject *parent = nullptr);
public:
    void ReceiveCanData(CHANNEL_HANDLE handle);
    int closeFlag = 0;//接收数据

public:
    void ReceiveCloseFlag(int close_Flag);
signals:
    void ThreadSendCanData(QString strCANID,QString strFormat,QString strType,QString strLen,QString strData);//通过信号的方式，将子线程中的数据发送给主线程
    void CloseThreadFlag();//子线程发送关闭子线程信号
    void SendHydraulicSystemsInfo(float pressOfPowerReal,float pressOfPumpReal,float temperatureReal);
protected:
    void run();
public slots:
};

#endif // RECEIVETHREAD_H
