#include "ToolBox.h"
#include "CustomWidget/ToolPage.h"
#include "ui_ToolBox.h"

ToolBox::ToolBox(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ToolBox)
{
    ui->setupUi(this);

    auto* widget = new QWidget(this);
    m_pContentVBoxLayout = new QVBoxLayout;
    m_pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pContentVBoxLayout->setSpacing(2);

    auto* vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->addLayout(m_pContentVBoxLayout);
    vBoxLayout->addStretch(1);

    ui->scrollArea->setWidget(widget);
}

ToolBox::~ToolBox()
{
    delete ui;
}

void ToolBox::AddItem()
{
    auto* page = new ToolPage(this);


    m_pContentVBoxLayout->addWidget(page);
}

void ToolBox::RemoveItem(ToolPage* RemovedItem) const
{
    if (RemovedItem)
    {
        RemovedItem->setParent(nullptr);
        m_pContentVBoxLayout->removeWidget(RemovedItem);
    }
}
