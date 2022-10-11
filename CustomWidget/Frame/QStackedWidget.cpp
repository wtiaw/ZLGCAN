#include "QStackedWidget.h"
#include "ui_QStackedWidget.h"

QStackedWidget::QStackedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QStackedWidget)
{
    ui->setupUi(this);
}

QStackedWidget::~QStackedWidget()
{
    delete ui;
}

void QStackedWidget::SetActiveIndex(int index)
{

}

void QStackedWidget::AddWidget(QWidget *InWidget)
{

}
