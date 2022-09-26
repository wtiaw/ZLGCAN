#include "AutoSendConfigWindow.h"
#include "CustomWidget/DataEdit.h"
#include "CustomWidget/ToolBox.h"
#include "ui_AutoSendConfigWindow.h"

AutoSendConfigWindow::AutoSendConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoSendConfigWindow)
{
    ui->setupUi(this);

    Init();
}

AutoSendConfigWindow::~AutoSendConfigWindow()
{
    delete ui;
}

void AutoSendConfigWindow::Init()
{
    AutoMessageConfig = new QAutoMessageConfig();
    AutoMessageConfig->ReadConfig();

    ToolBox* toolBox = new ToolBox();
    toolBox->AddItem(QStringLiteral("Qt小罗"), new DataEdit());
    toolBox->AddItem(QStringLiteral("Qt小罗"), new DataEdit());
    toolBox->AddItem(QStringLiteral("Qt小罗"), new DataEdit());
    toolBox->AddItem(QStringLiteral("Qt小罗"), new DataEdit());

    ui->verticalLayout->addWidget(toolBox);
}

void AutoSendConfigWindow::CreateItem()
{
//    QHBoxLayout* Layout;

//    Layout->addWidget()
//    ui->Container->addScrollBarWidget();
}
