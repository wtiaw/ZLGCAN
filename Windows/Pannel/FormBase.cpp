#include "FormBase.h"

FormBase::FormBase(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f)
    // ui(new Ui::ACR_H53_Form)
{
    // ui->setupUi(this);
    FormBase::Init();
}

FormBase::~FormBase()
{
    // delete ui;
}

void FormBase::Init()
{
    qDebug() << GetEnumKeyStr<CustomEnum::EFormType>(FromType) << "init";
}

void FormBase::InitVariable()
{
}

void FormBase::InitWindow()
{
    qDebug() << GetEnumKeyStr<CustomEnum::EFormType>(FromType) << "Init Window";
    
    InitButtonFunction();
}

void FormBase::InitButtonFunction()
{
}

void FormBase::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    
    InitVariable();
    InitWindow();
}
