#include "threadtst.h"
#include <QTime>
#include <QDebug>

ThreadTst::ThreadTst(QObject *parent) :
    QThread(parent)
{

}

ThreadTst::ThreadTst(QObject *parent, int tstinput) :
    QThread(parent)
{
    m_tstinput = tstinput;
}

//! [0]
ThreadTst::~ThreadTst()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}
//! [0]

void ThreadTst::run()
{
    bool currentPortNameChanged = false;

    m_threadCnt = 0;
    //m_mutex.lock();

    while (!m_quit) {

        qDebug()<<"ThreadTst running : "<<m_threadCnt++<<" !!!";
        emit this->response(tr("input:%1 thread running: %2")
                            .arg(m_tstinput).arg(m_threadCnt));
        sleep(1);
    }

    //m_mutex.unlock();

    //! [13]
}
