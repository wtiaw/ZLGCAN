#ifndef QRECEIVETHREAD_H
#define QRECEIVETHREAD_H

#include "CustomThread/QReceiveItem.h"
#include "mainwindow.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>
#include "QThreadBase.h"
#include "Library/QCANLibrary.h"

class QReceiveThread : public QThreadBase
{
    Q_OBJECT
public:
    explicit QReceiveThread(QObject *parent = nullptr);
    ~QReceiveThread();

    void run() override;
    void Stop() override;

    void AddTrigger(uint Id, QVector<BYTE>& FilterData);
    void AddTrigger(QReceiveItem* NewItem);
    void AddTrigger(QVector<QReceiveItem*> NewItems);

private:
    void ReceiveData(CHANNEL_HANDLE& ChannelHandle);

    void Reception(const CANData& Data);

private slots:
    void Test();

public:
signals:
    void AddCANTableData_T(const ZCAN_Transmit_Data& data);
    void AddCANFDTableData_T(const ZCAN_TransmitFD_Data& data);

    void AddCANTableData_R(const ZCAN_Receive_Data& data);
    void AddCANFDTableData_R(const ZCAN_ReceiveFD_Data& data);


    void AddTableData(const TableData& InTableData);

private:
    QTimer* Timer;
    QElapsedTimer* ElapsedTimer;

    MainWindow* mainWindow;

    QVector<QReceiveItem*> ReceiveItemContainer;

    canid_t FirstFrameId;
    BYTE length;
    QVector<BYTE> canData;
};


#endif // QRECEIVETHREAD_H
