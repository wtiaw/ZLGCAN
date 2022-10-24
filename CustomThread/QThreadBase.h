#ifndef QTHREADBASE_H
#define QTHREADBASE_H

#include <QThread>

class QThreadBase : public QThread
{
    Q_OBJECT
public:
    explicit QThreadBase(QObject *parent = nullptr);

    virtual void run() override;

    virtual void Stop();
    virtual void Pause();
    virtual void Resume();

protected:
    bool bIsPause;
};

#endif // QTHREADBASE_H
