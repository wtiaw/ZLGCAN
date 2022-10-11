#include "QTransmitThread.h"
#include "qdebug.h"

QTransmitThread::QTransmitThread(QObject *parent)
    : QThread{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);
}

void QTransmitThread::run()
{
    qDebug() << "当前子线程ID:" << QThread::currentThreadId();
    qDebug() << "开始执行线程";

    connect(this, SIGNAL(GetViewCanFrame(ZCAN_Transmit_Data&)), mainWindow, SLOT( GetViewCanFrame(ZCAN_Transmit_Data&)));
    connect(this, SIGNAL(GetViewCanFrame(ZCAN_TransmitFD_Data&)), mainWindow, SLOT( GetViewCanFrame(ZCAN_TransmitFD_Data&)));
    connect(this, SIGNAL(AddTableData(const ZCAN_Transmit_Data*,UINT)), mainWindow, SLOT( AddTableData(const ZCAN_Transmit_Data*,UINT)));
    connect(this, SIGNAL(AddTableData(const ZCAN_TransmitFD_Data*,UINT)), mainWindow, SLOT( AddTableData(const ZCAN_TransmitFD_Data*,UINT)));


    switch (mainWindow->GetCanTypeFromUI()) {
    case 0:
        TransmitCAN();
        break;
    case 1:
        TransmitCANFD();
        break;
    }


}

void QTransmitThread::TransmitCAN()
{
    ZCAN_Transmit_Data can_data;

    emit GetViewCanFrame(can_data);

    auto result = ZCAN_Transmit(mainWindow->GetChannelHandle(), &can_data, 1);
//    emit AddTableData(&can_data,1);
}

void QTransmitThread::TransmitCANFD()
{
    ZCAN_Transmit_Data can_data;

    emit GetViewCanFrame(can_data);

    auto result = ZCAN_Transmit(mainWindow->GetChannelHandle(), &can_data, 1);
    emit AddTableData(&can_data,1);
}
