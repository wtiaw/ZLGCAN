#include "FormBase.h"

FormBase::FormBase(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f)
    // ui(new Ui::ACR_H53_Form)
{
    // ui->setupUi(this);
}

FormBase::~FormBase()
{
    // delete ui;
}

void FormBase::InitWindow()
{
    InitButtonFunction();
}

void FormBase::InitButtonFunction()
{
}
