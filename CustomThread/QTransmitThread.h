#ifndef QTRANSMITTHREAD_H
#define QTRANSMITTHREAD_H

#include "mainwindow.h"
#include <QThread>

class QTransmitThread : public QThread
{
    Q_OBJECT
public:
    explicit QTransmitThread(QObject *parent = nullptr);

    void run() override;

private:
signals:
    void Transmit();

    //@biref 从面板获取CAN数据
    void GetViewCanFrame(ZCAN_Transmit_Data& can_data);
    void GetViewCanFrame(ZCAN_TransmitFD_Data& canfd_data);

    void AddTableData(const ZCAN_Transmit_Data* data, UINT len);
    void AddTableData(const ZCAN_TransmitFD_Data* data, UINT len);

private:
    void TransmitCAN();
    void TransmitCANFD();

private:
    MainWindow* mainWindow;
};

#endif // QTRANSMITTHREAD_H
