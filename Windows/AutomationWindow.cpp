#include "AutomationWindow.h"
#include "ui_AutomationWindow.h"
#include "Automation/AutomationNode_Loop.h"

AutomationWindow::AutomationWindow(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::AutomationWindow)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowTitle("自动化");

    AutomationSystemPtr = new AutomationSystem;
}

AutomationWindow::~AutomationWindow()
{
    delete ui;
}

void AutomationWindow::on_test_clicked()
{
    auto* Node1 = new AutomationNode_LoopStart;
    Node1->SetDelayTime(2000);
    Node1->SetLoopTime(5);

    connect(Node1, &AutomationNodeBase::On_Executed, [&]()
    {
        qDebug() << "Loop start";
    });
    AutomationSystemPtr->AddNode(Node1);
    

    int a = 0;
    while (a < 5)
    {
        auto Node2 = new AutomationNodeBase;
        Node2->SetDelayTime(100);

        connect(Node2, &AutomationNodeBase::On_Executed, [=]()
        {
            // Count++;
            // qDebug() << Count;
            qDebug()<<"Node"<<a;
        });


        AutomationSystemPtr->AddNode(Node2);
        a++;
    }

    auto* Node3 = new AutomationNode_LoopEnd;
    AutomationSystemPtr->AddNode(Node3);
    
    while (a < 10)
    {
        auto Node2 = new AutomationNodeBase;
        Node2->SetDelayTime(100);
    
        connect(Node2, &AutomationNodeBase::On_Executed, [=]()
        {
            // Count++;
            // qDebug() << Count;
            qDebug()<<"Node"<<a;
        });
    
    
        AutomationSystemPtr->AddNode(Node2);
        a++;
    }
    
    AutomationSystemPtr->Start();
}
