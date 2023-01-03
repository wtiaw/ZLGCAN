#include "AutomationSystem.h"

#include <QDebug>
#include <QTimer>

void AutomationSystem::Start()
{
    CurrentNode = FirstNode;

    Execute();
}

void AutomationSystem::AddNode(AutomationNodeBase* Node)
{
    if (!Node)
    {
        qDebug() << "Node is Null!";
        return;
    }

    if (!FirstNode)
    {
        FirstNode = Node;

        EndNode = FirstNode;
    }
    else
    {
        EndNode->SetNextNode(Node);
        EndNode = Node;
    }

    if (const auto LoopStart = qobject_cast<AutomationNode_LoopStart*>(Node))
    {
        LoopNodeStack.push(LoopStart);
    }
    else if (const auto LoopEnd = qobject_cast<AutomationNode_LoopEnd*>(Node))
    {
        const auto StartNode = LoopNodeStack.pop();

        StartNode->SetEndLoopNode(Node);
        LoopEnd->SetLoopStartNode(StartNode);
    }

    Size++;
}

void AutomationSystem::Execute()
{
    if (!CurrentNode)
    {
        qDebug() << "End";
        return;
    }

    if (const auto Start = qobject_cast<AutomationNode_LoopStart*>(CurrentNode); Start && Start->IsFinish())
    {
        On_Executed();
    }
    else
    {
        QTimer::singleShot(CurrentNode->GetDelayTime(), this, &AutomationSystem::On_Executed);
    }
}

void AutomationSystem::On_Executed()
{
    CurrentNode->Executed();
    CurrentNode = CurrentNode->GetNextNode();

    Execute();
}
