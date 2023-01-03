#pragma once

#include "AutomationNode.h"

class AutomationNode_LoopStart : public AutomationNodeBase
{
    Q_OBJECT

public:
    AutomationNode_LoopStart();

    void InitState();
    
    void SetEndLoopNode(AutomationNodeBase* InEndLoop);
    AutomationNodeBase* GetNextNode() override;

    void Executed() override;

    void SetLoopTime(uint Time);

    bool IsValid() const { return bIsValidLoop; }
    bool IsFinish() const { return bIsFinish; }

protected:
    AutomationNodeBase* EndLoop = nullptr;
    
    uint TargetTime{};
    uint Count{};

    bool bIsFinish;
    bool bIsValidLoop;
};

class AutomationNode_LoopEnd : public AutomationNodeBase
{
    Q_OBJECT

public:
    void SetLoopStartNode(AutomationNode_LoopStart* InLoopStartNode);

    AutomationNodeBase* GetNextNode() override;
    
protected:
    AutomationNode_LoopStart* LoopStartNode = nullptr;
};


