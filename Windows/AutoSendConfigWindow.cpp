#include "AutoSendConfigWindow.h"
#include "ui_AutoSendConfigWindow.h"

AutoSendConfigWindow::AutoSendConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoSendConfigWindow)
{
    ui->setupUi(this);
}

AutoSendConfigWindow::~AutoSendConfigWindow()
{
    delete ui;
}
