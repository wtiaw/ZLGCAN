#include "AutoSendConfigWindow.h"
#include "CustomWidget/ToolBox.h"
#include "CustomWidget/ToolPage.h"
#include "ui_AutoSendConfigWindow.h"

AutoSendConfigWindow::AutoSendConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoSendConfigWindow)
{
    setAttribute(Qt::WA_QuitOnClose, false);

    ui->setupUi(this);

    Init();
}

AutoSendConfigWindow::~AutoSendConfigWindow()
{
    delete ui;
}

void AutoSendConfigWindow::On_AddButtonClicked()
{
    CreateItem();
}

void AutoSendConfigWindow::On_DeleteButtonClicked()
{
    for(auto i : SelectItems)
    {
        toolBox->RemoveItem(i);
    }

    SelectItems.clear();
    ui->DeleteButton->setEnabled(false);
}

void AutoSendConfigWindow::On_AddSelectedItem(ToolPage *SelectedItem)
{
    SelectItems.append(SelectedItem);

    if(!ui->DeleteButton->isEnabled())
        ui->DeleteButton->setEnabled(true);
}

void AutoSendConfigWindow::On_RemoveSelectedItem(ToolPage *SelectedItem)
{
    SelectItems.removeOne(SelectedItem);

    if(SelectItems.length() == 0)
        ui->DeleteButton->setEnabled(false);
}

void AutoSendConfigWindow::Init()
{
    AutoMessageConfig = new QAutoMessageConfig();
    AutoMessageConfig->ReadConfig();

    toolBox = new ToolBox(this);
    ui->verticalLayout->addWidget(toolBox);

    ui->DeleteButton->setEnabled(false);

    connect(ui->AddButton, &QPushButton::clicked, this, &AutoSendConfigWindow::On_AddButtonClicked);
    connect(ui->DeleteButton, &QPushButton::clicked, this, &AutoSendConfigWindow::On_DeleteButtonClicked);
}

void AutoSendConfigWindow::CreateItem()
{
    toolBox->AddItem();
}

