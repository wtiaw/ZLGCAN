#include "QThreadBase.h"
#include "qdebug.h"

QThreadBase::QThreadBase(QObject *parent)
    : QThread{parent}
{

}

void QThreadBase::run()
{
    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Run";
}

void QThreadBase::Stop()
{
    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Stop";

    requestInterruption();
    quit();
    wait();
}

void QThreadBase::Pause()
{
    bIsPause = true;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Pause";
}

void QThreadBase::Resume()
{
    bIsPause = false;

    qDebug() <<"当前子线程ID:" << QThread::currentThreadId() << "Resume";
}
