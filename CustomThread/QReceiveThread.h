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

private:
    void ReceiveData(CHANNEL_HANDLE ChannelHandle);

private slots:
    void Test();

public:
signals:
    void AddTableData();

    void AddCANTableData(const ZCAN_Receive_Data* data, UINT len);
    void AddCANFDTableData(const ZCAN_ReceiveFD_Data* data, UINT len);

private:
    QTimer* Timer;
    QElapsedTimer* ElapsedTimer;

    MainWindow* mainWindow;

    bool bIsPause;
};

#endif // QRECEIVETHREAD_H
