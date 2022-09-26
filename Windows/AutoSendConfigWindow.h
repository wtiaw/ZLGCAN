#ifndef AUTOSENDCONFIGWINDOW_H
#define AUTOSENDCONFIGWINDOW_H

#include "Setting/QAutoMessageConfig.h"
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
    void Init();

    void CreateItem();

private:
    Ui::AutoSendConfigWindow *ui;

    QAutoMessageConfig* AutoMessageConfig;
};

#endif // AUTOSENDCONFIGWINDOW_H
