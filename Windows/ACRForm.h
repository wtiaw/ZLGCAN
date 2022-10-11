#ifndef ACRFORM_H
#define ACRFORM_H

#include <QWidget>

namespace Ui {
class ACRForm;
}

class ACRForm : public QWidget
{
    Q_OBJECT

public:
    explicit ACRForm(QWidget *parent = nullptr);
    ~ACRForm();

private:
    Ui::ACRForm *ui;
};

#endif // ACRFORM_H
