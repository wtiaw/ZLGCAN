#ifndef LOADDBCWINDOW_H
#define LOADDBCWINDOW_H

#include <QWidget>

namespace Ui {
class LoadDBCWindow;
}

class LoadDBCWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoadDBCWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~LoadDBCWindow() override;

private slots:
    void On_LoadDBCClicked();
    void On_SelectPathClicked();

private:
    Ui::LoadDBCWindow *ui;
};

#endif // LOADDBCWINDOW_H
