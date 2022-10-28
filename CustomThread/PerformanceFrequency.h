#ifndef PERFORMANCEFREQUENCY_H
#define PERFORMANCEFREQUENCY_H

#include <QThread>
#include <QObject>

class PerformanceFrequency : public QThread
{
    Q_OBJECT
public:
    explicit PerformanceFrequency(QObject *parent = nullptr);
    void setThreadRunning(uint Delay = 100, bool InSingle = false, uint mTime = 100);
    void setThreadStop();

Q_SIGNALS:
    void TimeOut();

protected:
    void run() override;

private:
    bool bRunning = false;
    bool Single = false;
    uint mTime = 100;
    uint delay = 100;
};

#endif // PERFORMANCEFREQUENCY_H
