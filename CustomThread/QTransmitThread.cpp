#include "QTransmitThread.h"
#include "qdebug.h"

QTransmitThread::QTransmitThread(QObject *parent)
    : QThreadBase{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);
    ElapsedTimer = new QElapsedTimer;
}

void QTransmitThread::run()
{
    qDebug() << "当前子线程ID:" << QThread::currentThreadId();
    qDebug() << "开始执行线程";

    bIsPause = false;

//    connect(this, SIGNAL(AddCANTableData(const ZCAN_Receive_Data*, UINT)), mainWindow, SLOT(AddTableData(const ZCAN_Receive_Data*, UINT)));
//    connect(this, SIGNAL(AddCANFDTableData(const ZCAN_ReceiveFD_Data*, UINT)), mainWindow, SLOT(AddTableData(const ZCAN_ReceiveFD_Data*, UINT)));
//    CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();

    while(!isInterruptionRequested()){
        if(!bIsPause){
            Test();
        }
        ElapsedTimer->start();
        msleep(0);
    }
}

void QTransmitThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}
