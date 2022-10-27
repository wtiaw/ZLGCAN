#ifndef QMESSAGETABLEWIDGET_H
#define QMESSAGETABLEWIDGET_H

#include "Data/FromeStruct.h"
#include "typedef.h"
#include <QTableWidget>
#include<windows.h>

struct MessageKeyInfo
{
    int MessageID;
    DirectionType directionType;

    MessageKeyInfo(){
        MessageID     = 0;
        directionType = DirectionType::None;
    }

    MessageKeyInfo(int InMessageID, DirectionType InDirectionType){
        MessageID     = InMessageID;
        directionType = InDirectionType;
    }

    bool operator < (const MessageKeyInfo &o) const
    {
        if(this->MessageID < o.MessageID)
        {
            return true;
        }
        else if(this->MessageID == o.MessageID)
        {
            if(this->directionType < o.directionType)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        return false;
    }
};

struct MessageValueInfo
{
    UINT64 intervalTimeNS;
    LARGE_INTEGER CPUintervalTimeNS;
    int TableIndex;
    int Count = 0;

    MessageValueInfo(){
        intervalTimeNS = 0;
        TableIndex     = 0;
        Count          = 0;
    }

    MessageValueInfo(UINT64 InIntervalTimeMS, int InTableIndex, LARGE_INTEGER InCPUintervalTimeNS){
        intervalTimeNS    = InIntervalTimeMS;
        TableIndex        = InTableIndex;
        CPUintervalTimeNS = InCPUintervalTimeNS;
    }
};

class QMessageTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    QMessageTableWidget(QWidget *parent = nullptr);

    class QStandardItemModel* TableViewModel ;

    QMap<MessageKeyInfo, MessageValueInfo> MessageIDMap;
};

#endif // QMESSAGETABLEWIDGET_H
