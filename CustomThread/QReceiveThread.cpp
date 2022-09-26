#include "QReceiveThread.h"
#include "qdebug.h"

QReceiveThread::QReceiveThread(QObject *parent)
    : QThread{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);
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

    connect(this, SIGNAL(AddTableData()), mainWindow, SLOT( ReceiveData()));

    while(!isInterruptionRequested()){
        if(!bIsPause){
            emit AddTableData();
        }
        msleep(10);
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

void QReceiveThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}
