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

//template<typename CANData>
//struct ReceptionData
//{
//    uint FrameId;
//    QVector<BYTE> FilterData;
//    std::function<void (const CANData &)> FuncNoMember = nullptr;
//    void (QReceiveThread::* FuncMember)() = nullptr;
//};

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

//    void InitReceptionData(CHANNEL_HANDLE& ChannelHandle);
//    template<typename CANData>
//    void AddReceptionData(const uint FrameID, const QVector<BYTE> FilterData, std::function<void (const CANData &)> const Func);

//    bool ShouldReception(const ZCAN_Receive_Data& Data, const ReceptionData<ZCAN_Receive_Data> InReceptionData);
//    bool ShouldReception(const ZCAN_ReceiveFD_Data& Data, const ReceptionData<ZCAN_ReceiveFD_Data> InReceptionData);

//    void Reception(const ZCAN_Receive_Data& Data);
//    void Reception(const ZCAN_ReceiveFD_Data& Data);

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
//    QVector<ReceptionData<ZCAN_ReceiveFD_Data>> ReceptionDatas;
};

//template<typename CANData>
//void QReceiveThread::AddReceptionData(const uint FrameID, const QVector<BYTE> FilterData, const std::function<void (const CANData &)> Func)
//{
//    ReceptionData<ZCAN_ReceiveFD_Data> Temp;

//    Temp.FrameId = FrameID;
//    Temp.FilterData = FilterData;
//    Temp.FuncNoMember = Func;

//    ReceptionDatas.append(Temp);
//}

//template<class ReceiveData>
//void QReceiveThread::Reception(ReceiveData Data)
//{
//    for(auto i : ReceiveItemContainer)
//    {

//    }
//}

#endif // QRECEIVETHREAD_H
