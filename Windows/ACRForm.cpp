#include "ACRForm.h"
#include "ui_ACRForm.h"

ACRForm::ACRForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ACRForm)
{
    ui->setupUi(this);

    setWindowTitle(QString("ACR"));
}

ACRForm::~ACRForm()
{
    delete ui;
}
