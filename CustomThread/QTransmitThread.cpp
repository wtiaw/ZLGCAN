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

    emit Fun();
    exec();
}

void QTransmitThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}
