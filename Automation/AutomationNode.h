#pragma once
#include <QObject>

class AutomationNodeBase : public QObject
{
    Q_OBJECT

public:
    AutomationNodeBase();
    
    virtual void Executed();

    void SetNextNode(AutomationNodeBase* InNextNode);
    
    virtual AutomationNodeBase* GetNextNode();

    [[nodiscard]] int GetDelayTime() const
    {
        return DelayTime;
    }

    void SetDelayTime(int InDelayTime)
    {
        this->DelayTime = InDelayTime;
    }

signals:
    void On_Executed();

protected:

    int DelayTime = 0;

protected:
    AutomationNodeBase* Next = nullptr;
};


