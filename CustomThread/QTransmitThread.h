#ifndef QTRANSMITTHREAD_H
#define QTRANSMITTHREAD_H

#include "mainwindow.h"
#include "QThreadBase.h"

class QTransmitThread : public QThreadBase
{
    Q_OBJECT
public:
    explicit QTransmitThread(QObject *parent = nullptr);

    void run() override;

private:
    void Test();

private:
    MainWindow* mainWindow;

    QElapsedTimer* ElapsedTimer;
};

#endif // QTRANSMITTHREAD_H
