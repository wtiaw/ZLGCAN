#ifndef AUTOSENDCONFIGWINDOW_H
#define AUTOSENDCONFIGWINDOW_H

#include <QWidget>

namespace Ui {
class AutoSendConfigWindow;
}

class AutoSendConfigWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AutoSendConfigWindow(QWidget *parent = nullptr);
    ~AutoSendConfigWindow();

private:
    Ui::AutoSendConfigWindow *ui;
};

#endif // AUTOSENDCONFIGWINDOW_H
