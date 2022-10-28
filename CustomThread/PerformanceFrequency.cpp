#include "PerformanceFrequency.h"
#include "qdebug.h"
#include<windows.h>
#include<stdio.h>

PerformanceFrequency::PerformanceFrequency(QObject *parent)
    : QThread{parent}
{

}

void PerformanceFrequency::setThreadRunning(uint Delay, bool InSingle, uint mTime)
{
    this->mTime = mTime * 1000 - 1500;
    this->delay = Delay * 1000;
    bRunning = true;
    Single = InSingle;

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
    usleep(delay);
    while(bRunning)
    {
//        LARGE_INTEGER nFreq;
//        LARGE_INTEGER t1;
//        LARGE_INTEGER t2;

//        double dt;

//        QueryPerformanceFrequency(&nFreq);
//        QueryPerformanceCounter(&t1);


        emit TimeOut();

        if(Single)
        {
           break;
        }
        usleep(mTime);


//        QueryPerformanceCounter(&t2);
//        dt =(t2.QuadPart -t1.QuadPart)/(double)nFreq.QuadPart;


//        qDebug()<<"Run.elapsed ="<<dt * 1000000<<"ns";
    }

//    exec();
}
