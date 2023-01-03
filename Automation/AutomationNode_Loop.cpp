#include "AutomationNode_Loop.h"
#include <QDebug>

AutomationNode_LoopStart::AutomationNode_LoopStart()
{
}

void AutomationNode_LoopStart::InitState()
{
    Count = 0;
    bIsFinish = false;
}

void AutomationNode_LoopStart::SetEndLoopNode(AutomationNodeBase* InEndLoop)
{
    bIsValidLoop = true;
    EndLoop = InEndLoop;
}

AutomationNodeBase* AutomationNode_LoopStart::GetNextNode()
{
    if (Count > TargetTime)
    {
        return EndLoop;
    }
    else
    {
        if (Count == TargetTime)
        {
            bIsFinish = true;
        }
        
        qDebug() << "Loop Time" << Count;
        return AutomationNodeBase::GetNextNode();
    }
}

void AutomationNode_LoopStart::Executed()
{
    AutomationNodeBase::Executed();

    Count++;
}

void AutomationNode_LoopStart::SetLoopTime(const uint Time)
{
    TargetTime = Time;
}

void AutomationNode_LoopEnd::SetLoopStartNode(AutomationNode_LoopStart* InLoopStartNode)
{
    LoopStartNode = InLoopStartNode;
}

AutomationNodeBase* AutomationNode_LoopEnd::GetNextNode()
{
    if (LoopStartNode->IsFinish())
    {
        LoopStartNode->InitState();
        return AutomationNodeBase::GetNextNode();
    }
    else
    {
        return LoopStartNode;
    }
}
