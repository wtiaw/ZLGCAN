#include "ReceiveThread.h"
#include "qdebug.h"


ReceiveThread::ReceiveThread(QObject *parent)
{

}

void ReceiveThread::ReceiveCanData(CHANNEL_HANDLE chandle)
{
    VCI_CAN_OBJ frameinfo[1000];

    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;
    while(start_)
    {
        if (len = ZCAN_GetReceiveNum(chandle, TYPE_CAN))
        {
            len = ZCAN_Receive(chandle, can_data, 100, 50);
            AddData(can_data, len);
        }
        if (len = ZCAN_GetReceiveNum(chandle, TYPE_CANFD))
        {
            len = ZCAN_ReceiveFD(chandle, canfd_data, 100, 50);
            AddData(canfd_data, len);
        }
        //避免无数据时变成While(1),会占用大量的CPU
        Sleep(15);
    }
}


void ReceiveThread::run()
{
//    ReceiveCanData();
}
