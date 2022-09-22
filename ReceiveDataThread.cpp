#include "ReceiveDataThread.h"
#include "qdebug.h"

ReceiveDataThread::ReceiveDataThread(QObject *parent)
    : QThread{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);
}

ReceiveDataThread::~ReceiveDataThread()
{
    Stop();
}

void ReceiveDataThread::run()
{
    qDebug() << "当前子线程ID:" << QThread::currentThreadId();
    qDebug() << "开始执行线程";

    bIsPause = false;

    connect(this, SIGNAL(AddTableData()), mainWindow, SLOT( ReceiveData()));

    while(!isInterruptionRequested()){
        if(!bIsPause){
            emit AddTableData();
        }
        msleep(10);
    }
}

void ReceiveDataThread::Stop()
{
    requestInterruption();
    quit();
    wait();
}

void ReceiveDataThread::Pause()
{
    bIsPause = true;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Pause";
}

void ReceiveDataThread::Resume()
{
    bIsPause = false;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Resume";
}

void ReceiveDataThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}
