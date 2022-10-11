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

public slots:
    void On_AddButtonClicked();
    void On_DeleteButtonClicked();

    void On_AddSelectedItem(class ToolPage* SelectedItem);
    void On_RemoveSelectedItem(class ToolPage* SelectedItem);

private:
    void Init();

    void CreateItem();

private:
    Ui::AutoSendConfigWindow *ui;

    class ToolBox* toolBox;

    QAutoMessageConfig* AutoMessageConfig;

    QVector<class ToolPage*> SelectItems;
};

#endif // AUTOSENDCONFIGWINDOW_H
