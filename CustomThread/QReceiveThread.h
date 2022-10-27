#ifndef QRECEIVETHREAD_H
#define QRECEIVETHREAD_H

#include "mainwindow.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <QMutex>
#include "QThreadBase.h"
#include "Library/QCANLibrary.h"

struct ReceptionData
{
    uint FrameId;
    QVector<BYTE> FilterData;
    std::function<void ()> FuncNoMember = nullptr;
    void (QReceiveThread::* FuncMember)() = nullptr;
};

class QReceiveThread : public QThreadBase
{
    Q_OBJECT
public:
    explicit QReceiveThread(QObject *parent = nullptr);
    ~QReceiveThread();

    void run() override;
    void Stop() override;

private:
    void ReceiveData(CHANNEL_HANDLE& ChannelHandle);

    void InitReceptionData(CHANNEL_HANDLE& ChannelHandle);
    void AddReceptionData(const uint FrameID, const QVector<BYTE> FilterData, std::function<void ()> const Func);

    bool ShouldReception(const ZCAN_Receive_Data& Data, const ReceptionData InReceptionData);
    bool ShouldReception(const ZCAN_ReceiveFD_Data& Data, const ReceptionData InReceptionData);

    void Reception(const ZCAN_Receive_Data& Data);
    void Reception(const ZCAN_ReceiveFD_Data& Data);

    template<typename ReceiveData>
    void Reception(const ReceiveData& Data);

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

    QVector<ReceptionData> ReceptionDatas;
};

//template<typename ReceiveData>
//void QReceiveThread::Reception(const ReceiveData& Data)
//{
//    for(auto& i : ReceptionDatas)
//    {
//        if(ShouldReception(Data,i))
//        {
//            if(i.FuncNoMember)
//                i.FuncNoMember();

//            if(i.FuncMember)
//                (this->*i.FuncMember)();

//            return;
//        }
//    }
//}

#endif // QRECEIVETHREAD_H
