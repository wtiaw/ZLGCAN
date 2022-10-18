#include "QReceiveThread.h"
#include "qdebug.h"

QReceiveThread::QReceiveThread(QObject *parent)
    : QThread{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);

    moveToThread(this);
}

QReceiveThread::~QReceiveThread()
{
    Stop();
}

void QReceiveThread::run()
{
    qDebug() << "当前子线程ID:" << QThread::currentThreadId();
    qDebug() << "开始执行线程";

    bIsPause = false;

    connect(this, SIGNAL(AddCANTableData(const ZCAN_Receive_Data*, UINT)), mainWindow, SLOT(AddTableData(const ZCAN_Receive_Data*, UINT)));
    connect(this, SIGNAL(AddCANFDTableData(const ZCAN_ReceiveFD_Data*, UINT)), mainWindow, SLOT(AddTableData(const ZCAN_ReceiveFD_Data*, UINT)));
    CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();

    while(!isInterruptionRequested()){
        if(!bIsPause){
            ReceiveData(chHandle);
//            emit AddTableData();
        }
        msleep(15);
    }
}

void QReceiveThread::Stop()
{
    requestInterruption();
    quit();
    wait();
}

void QReceiveThread::Pause()
{
    bIsPause = true;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Pause";
}

void QReceiveThread::Resume()
{
    bIsPause = false;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Resume";
}

void QReceiveThread::ReceiveData(CHANNEL_HANDLE ChannelHandle)
{
    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CAN))
    {
        len = ZCAN_Receive(ChannelHandle, can_data, 100, 10);

        emit AddCANTableData(can_data, len);
    }
    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CANFD))
    {
        len = ZCAN_ReceiveFD(ChannelHandle, canfd_data, 100, 10);
        emit AddCANFDTableData(canfd_data, len);
    }
}

void QReceiveThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}
