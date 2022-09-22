#ifndef RECEIVEDATATHREAD_H
#define RECEIVEDATATHREAD_H

#include "mainwindow.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>

class ReceiveDataThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveDataThread(QObject *parent = nullptr);
    ~ReceiveDataThread();

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

#endif // RECEIVEDATATHREAD_H
