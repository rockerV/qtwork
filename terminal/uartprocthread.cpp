#include "uartprocthread.h"
#include <QSerialPort>
#include <QTime>
#include <QDebug>
#include "conf.h"

UartProcThread::UartProcThread(QObject *parent) :
    QThread(parent)
{

}

UartProcThread::UartProcThread(QObject *parent, QSerialPort *pSerial) :
    QThread(parent)
{
    m_serialRecv = pSerial;
}

//! [0]
UartProcThread::~UartProcThread()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void UartProcThread::run()
{

}

