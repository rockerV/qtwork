#ifndef THREADTST_H
#define THREADTST_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class ThreadTst : public QThread
{
    Q_OBJECT

public:
    explicit ThreadTst(QObject *parent = nullptr);
    explicit ThreadTst(QObject *parent = nullptr, int tstinput = 0);
    ~ThreadTst();



signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

private:
    void run() override;

    int m_tstinput;
    int m_threadCnt;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;
};

#endif // THREADTST_H

