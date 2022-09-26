#ifndef QRECEIVETHREAD_H
#define QRECEIVETHREAD_H

#include "mainwindow.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>

class QReceiveThread : public QThread
{
    Q_OBJECT
public:
    explicit QReceiveThread(QObject *parent = nullptr);
    ~QReceiveThread();

    void run() override;

    void Stop();
    void Pause();
    void Resume();

private slots:
    void Test();

private:
signals:
    void AddTableData();

private:
    QTimer* Timer;
    QElapsedTimer* ElapsedTimer;

    MainWindow* mainWindow;

    bool bIsPause;
};

#endif // QRECEIVETHREAD_H
