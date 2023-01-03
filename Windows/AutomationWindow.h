#ifndef AUTOMATIONWINDOW_H
#define AUTOMATIONWINDOW_H

#include <QWidget>

#include "Automation/AutomationSystem.h"

namespace Ui {
class AutomationWindow;
}

class AutomationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AutomationWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AutomationWindow();

    int Count = 0;

private slots:
    void on_test_clicked();
    
private:
    Ui::AutomationWindow *ui;

    AutomationSystem* AutomationSystemPtr;
};

#endif // AUTOMATIONWINDOW_H
