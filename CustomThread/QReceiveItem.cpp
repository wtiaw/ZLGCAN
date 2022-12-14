#include "QReceiveItem.h"

#include <utility>
#include "qdebug.h"

QReceiveItem::QReceiveItem(QObject *parent)
    : QObject{parent}
{

}

bool QReceiveItem::ContainedTrigger(const CANData &Data)
{
    if(FrameId != Data.can_id) return false;

    for(int i = 0 ; i < FilterData.length() ; i++)
    {
        if(FilterData[i] != Data.Data[i]) return false;
    }

    return true;
}

void QReceiveItem::ConstructTrigger(const uint Id, QVector<BYTE> FilterData, const QObject* context, const std::function<void (const CANData &)> Func)
{
    SetTrigger(Id, std::move(FilterData));
    if(context)
        connect(this, &QReceiveItem::Trigger, context, Func);
}

void QReceiveItem::On_Trigger(const CANData &Data)
{
//    QString str;
//    for (UINT i = 0; i < Data.canfd.frame.len; ++i)
//    {
//        str += QString("%1 ").arg(Data.canfd.frame.data[i], 2, 16, QLatin1Char('0'));
//    }
//    qDebug()<<str;
    emit Trigger(Data);
}

void QReceiveItem::SetTrigger(const uint Id, const QVector<BYTE> & FilterData)
{
    this->FrameId    = Id;
    this->FilterData = FilterData;
}
