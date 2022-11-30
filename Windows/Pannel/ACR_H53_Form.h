#ifndef ACR_H53_FORM_H
#define ACR_H53_FORM_H

#include <QWidget>

#include "FormBase.h"

namespace Ui {
class ACR_H53_Form;
}

class ACR_H53_Form final : public FormBase
{
    Q_OBJECT

public:
    explicit ACR_H53_Form(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ACR_H53_Form() override;

private:
    Ui::ACR_H53_Form *ui;
};

#endif // ACR_H53_FORM_H
