#include "PerformanceFrequency.h"
#include "qdatetime.h"

#include<windows.h>
#include<stdio.h>

PerformanceFrequency::PerformanceFrequency(QObject *parent)
    : QThread{parent}
{

}

void PerformanceFrequency::setThreadRunning(uint mTime)
{
    this->mTime = mTime * 1000 - 1500;
    bRunning = true;

    start();
}

void PerformanceFrequency::setThreadStop()
{
//    requestInterruption();
    bRunning = false;
    quit();
//    wait();
}

void PerformanceFrequency::run()
{
//    while(!isInterruptionRequested())
    while(bRunning)
    {
        LARGE_INTEGER nFreq;
        LARGE_INTEGER t1;
        LARGE_INTEGER t2;

        double dt;

        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&t1);


        emit TimeOut();
        usleep(mTime);

        QueryPerformanceCounter(&t2);
        dt =(t2.QuadPart -t1.QuadPart)/(double)nFreq.QuadPart;


        qDebug()<<"Run.elapsed ="<<dt * 1000000<<"ns";
    }
}
