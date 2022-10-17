#ifndef ACRFORM_H
#define ACRFORM_H

#include "typedef.h"
#include "zlgcan.h"
#include <QWidget>

namespace Ui {
class ACRForm;
}

class ACRForm : public QWidget
{
    Q_OBJECT

public:
    explicit ACRForm(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ACRForm();

private:
    void ConstructCAN(ZCAN_Transmit_Data &can_data, BYTE DLC, BYTE Data[], BYTE TransmitType);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ACRForm *ui;

    class MainWindow* mainWindow;
};

#endif // ACRFORM_H
