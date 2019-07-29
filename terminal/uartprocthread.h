#ifndef UARTPROCTHREAD_H
#define UARTPROCTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSerialPort>
#include "queue.h"


//! [0]
class UartProcThread : public QThread
{
    Q_OBJECT

public:
    explicit UartProcThread(QObject *parent = nullptr);
    explicit UartProcThread(QObject *parent = nullptr, QSerialPort *pSerial = nullptr);
    ~UartProcThread();

    void transaction(const QString &portName, int waitTimeout, const QString &request);
    int rpcProcess_sub1g(void);

    void updataInfo(QSerialPort *serial);

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

private:
    void run() override;
    void runExample();
    void runTest();

    QSerialPort *m_serialRecv = nullptr;
    llq_t *m_pllq;

    QString m_portName;
    QString m_request;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;
};
//! [0]



#endif // UARTPROCTHREAD_H
