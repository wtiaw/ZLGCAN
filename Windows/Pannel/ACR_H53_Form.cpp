#include "ACR_H53_Form.h"
#include "ui_ACR_H53_Form.h"

ACR_H53_Form::ACR_H53_Form(QWidget* parent, Qt::WindowFlags f) :
    FormBase(parent, f),
    ui(new Ui::ACR_H53_Form)
{
    ui->setupUi(this);

    FromType = CustomEnum::ACR_H53;
}

ACR_H53_Form::~ACR_H53_Form()
{
    delete ui;
}
