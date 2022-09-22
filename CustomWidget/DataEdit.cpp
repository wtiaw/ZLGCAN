#include "DataEdit.h"
#include "qtimer.h"
#include "qvalidator.h"

DataEdit::DataEdit()
{
    connect(this, SIGNAL(textChanged(const QString)), this, SLOT(On_TextChanged(const QString)));
    connect(this, SIGNAL(editingFinished()), this, SLOT(On_editingFinished()));

    setMaximumWidth(30);

    QSizePolicy sizePolicy = this->sizePolicy();
    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);

    QRegularExpression regx("[A-Fa-f0-9]{0,2}");
    QValidator* validator = new QRegularExpressionValidator(regx, this);
    setValidator(validator);
}

void DataEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);

     QTimer::singleShot(0, this, &QLineEdit::selectAll);
}

void DataEdit::On_TextChanged(const QString &arg1)
{
    setText(arg1.toUpper());

    if(arg1.length() == 2){
        emit editingFinished();
    }
}

void DataEdit::On_editingFinished()
{
    if(NextEdit){
        NextEdit->setFocus();
    }

    while(text().length() != 2){
        QString temp = "0";
        temp += text();
        setText(temp);
    }
}
