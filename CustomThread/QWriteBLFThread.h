#ifndef QWRITEBLFTHREAD_H
#define QWRITEBLFTHREAD_H

#include <QThread>

class QWriteBLFThread : public QThread
{
    Q_OBJECT
public:
    explicit QWriteBLFThread(QObject *parent = nullptr);

    virtual void run() override;
};

#endif // QWRITEBLFTHREAD_H
