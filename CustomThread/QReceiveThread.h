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

private:
    void ReceiveData(CHANNEL_HANDLE ChannelHandle);

    void InitReceptionData(CHANNEL_HANDLE ChannelHandle);
    void AddReceptionData(const uint FrameID, const QVector<BYTE> FilterData, std::function<void ()> const Func);

    bool ShouldReception(const ZCAN_Receive_Data& Data, const ReceptionData InReceptionData);
    bool ShouldReception(const ZCAN_ReceiveFD_Data& Data, const ReceptionData InReceptionData);

    void Reception(const ZCAN_Receive_Data& Data);
    void Reception(const ZCAN_ReceiveFD_Data& Data);

private slots:
    void Test();

public:
signals:
    void AddCANTableData(const ZCAN_Receive_Data* data, UINT len);
    void AddCANFDTableData(const ZCAN_ReceiveFD_Data* data, UINT len);

    void AddTableData(const TableData& InTableData);

private:
    QTimer* Timer;
    QElapsedTimer* ElapsedTimer;

    MainWindow* mainWindow;

    QVector<ReceptionData> ReceptionDatas;
};

#endif // QRECEIVETHREAD_H
