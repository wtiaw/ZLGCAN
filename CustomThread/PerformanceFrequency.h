#ifndef PERFORMANCEFREQUENCY_H
#define PERFORMANCEFREQUENCY_H

#include <QThread>
#include <QObject>

class PerformanceFrequency : public QThread
{
    Q_OBJECT
public:
    explicit PerformanceFrequency(QObject *parent = nullptr);
    void setThreadRunning(uint mTime);
    void setThreadStop();

Q_SIGNALS:
    void TimeOut();

protected:
    void run() override;

private:
    bool bRunning = false;
    uint mTime = 1;
};

#endif // PERFORMANCEFREQUENCY_H
