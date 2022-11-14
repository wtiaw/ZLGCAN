#include "ToolPage.h"
#include "CustomWidget/CheckBox/QDrawerCheckBox.h"
#include "Library/QWidgetLibrary.h"
#include "Windows/AutoSendConfigWindow.h"
#include "ui_ToolPage.h"

ToolPage::ToolPage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ToolPage)
{
    ui->setupUi(this);

    InitBase();

    InitMessageFrameTypeComboBox();

    InitMessageDLC();
    InitMessageId();

    InitData();
}

ToolPage::~ToolPage()
{
    delete ui;
}

void ToolPage::InitBase()
{
    ui->verticalLayoutContent_2->setAttribute(Qt::WA_StyledBackground);

    DrawerCheckBox = new QDrawerCheckBox;
    DrawerCheckBox->setText(QString("Test"));
    ui->TitleLayout->addWidget(DrawerCheckBox);

    EnableCheckBox = new QCheckBox;
    EnableCheckBox->setText(QString("启用"));
    EnableCheckBox->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    EnableCheckBox->setStyleSheet(R"(
                                  QCheckBox{
                                      color:rgb(200,200,200);
                                  })");

    QSizePolicy sizePolicy = EnableCheckBox->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    EnableCheckBox->setSizePolicy(sizePolicy);
    EnableCheckBox->setSizePolicy(QSizePolicy());

    ui->TitleLayout->addWidget(EnableCheckBox);

    connect(DrawerCheckBox, &QDrawerCheckBox::clicked, this, &ToolPage::On_ExpandClicked);
    connect(EnableCheckBox, &QCheckBox::clicked, this, &ToolPage::On_EnableCheckBoxClicked);
    connect(ui->SelectCheckBox, &QCheckBox::clicked, this, &ToolPage::On_SelectCheckBoxClicked);

    connect(this, &ToolPage::AddSelectedItem, qobject_cast<AutoSendConfigWindow*>(parent()->parent()),
            &AutoSendConfigWindow::On_AddSelectedItem);
    connect(this, &ToolPage::RemoveSelectedItem, qobject_cast<AutoSendConfigWindow*>(parent()->parent()),
            &AutoSendConfigWindow::On_RemoveSelectedItem);

    collapse();
}

void ToolPage::InitData()
{
    QWidgetLibrary::CreateDataEdit(ui->DataContainer, ui->DLCEdit, DataEdits);
}

void ToolPage::InitMessageFrameTypeComboBox() const
{
    QWidgetLibrary::InitMessageFrameTypeComboBox(ui->MessageTypeComboBox);
}

void ToolPage::InitMessageId()
{
    QWidgetLibrary::InitMessageID(ui->MessageIDEdit);

    connect(ui->MessageIDEdit, &QLineEdit::textChanged, this, &ToolPage::On_MessageIDChanged);
}

void ToolPage::InitMessageDLC()
{
    QWidgetLibrary::InitMessageDLC(ui->DLCEdit);

    connect(ui->DLCEdit, &QLineEdit::textChanged, this, &ToolPage::On_MessageDLCChanged);
}

bool ToolPage::CheckDLCData() const
{
    return QWidgetLibrary::CheckDLCData(ui->DLCEdit, ui->MessageTypeComboBox);
}

void ToolPage::AddWidget(const QString& title, QWidget* widget) const
{
    ui->verticalLayoutContent->addWidget(widget);
}

void ToolPage::expand() const
{
    ui->verticalLayoutContent_2->show();
}

void ToolPage::collapse() const
{
    ui->verticalLayoutContent_2->hide();
}

void ToolPage::On_ExpandClicked(const bool bClick) const
{
    if (bClick)
    {
        expand();
    }
    else
    {
        collapse();
    }
}

void ToolPage::On_EnableCheckBoxClicked(const bool bClick) const
{
    if (bClick)
    {
        DrawerCheckBox->setStyleSheet(QDrawerCheckBox::EnableQss);
        EnableCheckBox->setStyleSheet(R"(
                                      QCheckBox{
                                          color:rgb(0,0,0);
                                      })");
    }
    else
    {
        DrawerCheckBox->setStyleSheet(QDrawerCheckBox::DisableQss);
        EnableCheckBox->setStyleSheet(R"(
                                      QCheckBox{
                                          color:rgb(200,200,200);
                                      })");
    }
}

void ToolPage::On_SelectCheckBoxClicked(const bool bClick)
{
    if (bClick)
    {
        emit AddSelectedItem(this);
    }
    else
    {
        emit RemoveSelectedItem(this);
    }
}

void ToolPage::On_MessageIDChanged(const QString& arg1) const
{
    ui->MessageIDEdit->setText(arg1.toUpper());
}

void ToolPage::On_MessageDLCChanged(const QString& arg1)
{
    if (CheckDLCData() || ui->DLCEdit->text() == "")
    {
        InitData();
    }
}
