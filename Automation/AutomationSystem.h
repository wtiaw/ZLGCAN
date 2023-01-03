#pragma once
#include <QObject>
#include <qstack.h>

#include "AutomationNode.h"
#include "AutomationNode_Loop.h"


class AutomationSystem : public QObject
{
    Q_OBJECT
    
public:
    void Start();

    void AddNode(AutomationNodeBase* Node);

    [[nodiscard]] uint GetSize() const { return Size; }

private:
    void Execute();
    void On_Executed();
    
private:
    AutomationNodeBase* FirstNode = nullptr;
    AutomationNodeBase* EndNode = nullptr;
    
    AutomationNodeBase* CurrentNode = nullptr;

    uint Size{};

    QStack<AutomationNode_LoopStart*> LoopNodeStack;
};
