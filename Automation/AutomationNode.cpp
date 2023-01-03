#include "AutomationNode.h"
#include <QTimer>
#include <QDebug>

AutomationNodeBase::AutomationNodeBase()
{
    
}

void AutomationNodeBase::Executed()
{
    emit On_Executed();
}

void AutomationNodeBase::SetNextNode(AutomationNodeBase* InNextNode)
{
    Next = InNextNode;
}

AutomationNodeBase* AutomationNodeBase::GetNextNode()
{
    return Next;
}


