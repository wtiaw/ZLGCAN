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
    explicit FormBase(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~FormBase() override;

public:
    virtual void InitButtonFunction();

    void showEvent(QShowEvent* event) override;

    [[nodiscard]] CustomEnum::EFormType GetFromType() const
    {
        return FromType;
    }
    
    //界面显示时调用
    virtual void InitWindow();
    
protected:
    //构造函数中调用
    virtual void Init();

    virtual void InitVariable();


protected:
    CustomEnum::EFormType FromType = CustomEnum::None;
    //
    // private:
    //     Ui::ACR_H53_Form *ui;
};

#endif // ACR_H53_FORM_H
