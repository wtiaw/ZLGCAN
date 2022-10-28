#include "QReceiveItem.h"
#include "qdebug.h"

QReceiveItem::QReceiveItem(QObject *parent)
    : QObject{parent}
{

}

bool QReceiveItem::ContaineTrigger(const CANData &Data)
{
    if(Data.IsCanFD)
    {
        if(FrameId != Data.canfd.frame.can_id) return false;
        for(int i = 0 ; i < FilterData.length() ; i++)
        {
            if(FilterData[i] != Data.canfd.frame.data[i]) return false;
        }
    }
    else
    {
        if(FrameId != Data.can.frame.can_id) return false;
        for(int i=0;i<FilterData.length();i++)
        {
            if(FilterData[i] != Data.can.frame.data[i]) return false;
        }
    }
    return true;
}

void QReceiveItem::ConstructTrigger(uint Id, QVector<BYTE> FilterData, const std::function<void (const CANData &)> Func)
{
    SetTrigger(Id, FilterData);
    connect(this, &QReceiveItem::Trigger, this, Func, Qt::QueuedConnection);
}

void QReceiveItem::On_Trigger(const CANData &Data)
{
    QString str;
    for (UINT i = 0; i < Data.canfd.frame.len; ++i)
    {
        str += QString("%1 ").arg(Data.canfd.frame.data[i], 2, 16, QLatin1Char('0'));
    }
    qDebug()<<str;
    emit Trigger(Data);
}

void QReceiveItem::SetTrigger(uint Id, QVector<BYTE> FilterData)
{
    this->FrameId    = Id;
    this->FilterData = FilterData;
}
