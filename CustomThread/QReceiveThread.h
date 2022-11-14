#ifndef QRECEIVETHREAD_H
#define QRECEIVETHREAD_H

#include "CustomThread/QReceiveItem.h"
#include "mainwindow.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>
#include "QThreadBase.h"

class QReceiveThread final : public QThreadBase
{
    Q_OBJECT
public:
    explicit QReceiveThread(QObject* parent = nullptr);
    ~QReceiveThread() override;

    void run() override;
    void Stop() override;

    void AddTrigger(uint Id, const QVector<BYTE>& FilterData);
    void AddTrigger(QReceiveItem* NewItem);
    void AddTrigger(const QVector<QReceiveItem*>& NewItems);

private:
    void ReceiveData(const CHANNEL_HANDLE& ChannelHandle);

    void Reception(const CANData& Data);

private slots:
    void Test() const;

public:
signals:
    void AddCANTableData_R(const ZCAN_Receive_Data& data);
    void AddCANFDTableData_R(const ZCAN_ReceiveFD_Data& data);

    void TransmitCAN(ZCAN_Transmit_Data& canfd_data);
    void TransmitCANFD(ZCAN_TransmitFD_Data& canfd_data);

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
