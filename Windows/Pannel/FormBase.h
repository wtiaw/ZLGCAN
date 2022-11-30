#ifndef FORMBASE_H
#define FORMBASE_H

#include <QWidget>

#include "Data/CustomEnum.h"

// namespace Ui {
// class ACR_H53_Form;
// }

class FormBase : public QWidget
{
    Q_OBJECT

public:
    explicit FormBase(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FormBase() override;

public:
    virtual void InitWindow();
    virtual void InitButtonFunction();

    [[nodiscard]] CustomEnum::EFormType GetFromType() const
    {
        return FromType;
    }

protected:
    CustomEnum::EFormType FromType;
//
// private:
//     Ui::ACR_H53_Form *ui;
};

#endif // ACR_H53_FORM_H
