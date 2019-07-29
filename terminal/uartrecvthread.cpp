#include <QSerialPort>
#include <QTime>
#include <QDebug>
#include "uartrecvthread.h"
#include "conf.h"


UartRecvThread::UartRecvThread(QObject *parent) :
    QThread(parent)
{
}

UartRecvThread::UartRecvThread(QObject *parent, QSerialPort *pSerial) :
    QThread(parent)
{
    m_serialRecv = pSerial;
}

//! [0]
UartRecvThread::~UartRecvThread()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}
//! [0]

//! [1] //! [2]
void UartRecvThread::transaction(const QString &portName, int waitTimeout, const QString &request)
{
    //! [1]
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_request = request;
    //! [3]
    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}
//! [2] //! [3]

void UartRecvThread::run()
{
    rpcProcess_sub1g();
    //runTest();
}
void UartRecvThread::runTest()
{
#if 1
    int32_t rpcLen, rpcTempLen, bytesRead, rpcBuffIdx;
    char retryAttempts = 0, rpcBuff[GH20_RX_FRAME_LEN_MAX];
    //m_pserial->read(&rpcBuff[0], 1);
    //qDebug()<<"result:"<<rpcBuff[0];

    while(1)
    {
        if (m_serialRecv->isOpen())
        {
            //m_serialRecv->waitForReadyRead(-1);
            //for (int i = 0; i < 10; i++)
            int i = 0;
            rpcLen = 0;
            while(m_serialRecv->size())
            {
                bytesRead = m_serialRecv->read(&rpcBuff[rpcLen], 1);
                if (bytesRead)
                {
                    rpcLen += bytesRead;
                    qDebug()<<"time="<<i++<<".bytesRead="<<bytesRead;
                }
            }
            if (rpcLen)
            {
                rpcBuff[rpcLen] = 0;
                qDebug()<<"len="<<rpcLen<<".result:"<<rpcBuff;
            }

        }
    }


    while(1)
    {
        if (m_serialRecv->isOpen())
        {
            rpcLen = 0;
            m_serialRecv->waitForReadyRead(-1);
            while (1)
            {
                qDebug()<<"size="<<m_serialRecv->size();
                qDebug()<<"bytesAvailable="<<m_serialRecv->bytesAvailable();
                qDebug()<<"readBufferSize="<<m_serialRecv->readBufferSize();
                qDebug()<<"isReadable="<<m_serialRecv->isReadable();

                bytesRead = m_serialRecv->read(&rpcBuff[0], 10);

                qDebug()<<"bytesRead="<<bytesRead;

                if (bytesRead <= 0)
                    break;
                rpcLen += bytesRead;
                while(bytesRead)
                {
                    qDebug()<<"size="<<m_serialRecv->size();
                    qDebug()<<"bytesAvailable="<<m_serialRecv->bytesAvailable();
                    qDebug()<<"readBufferSize="<<m_serialRecv->readBufferSize();
                    qDebug()<<"isReadable="<<m_serialRecv->isReadable();

                    bytesRead = m_serialRecv->read(&rpcBuff[rpcLen], 10);

                    qDebug()<<"bytesRead="<<bytesRead;


                    rpcLen += bytesRead;
                }
                if (rpcLen)
                {
                    rpcBuff[rpcLen] = 0;
                    qDebug()<<"len="<<rpcLen<<".result:"<<rpcBuff;
                    rpcLen = 0;
                }
                break;

                //                QByteArray responseData = m_serialRecv->readAll();
                //                while (m_serialRecv->waitForReadyRead(100))
                //                    responseData += m_serialRecv->read(20);
                //                const QString response = QString::fromUtf8(responseData);
                //                qDebug()<<"result:"<<response;
                //                emit this->response(response);

            }

        }
    }
#else
    while(1)
    {
        qDebug()<<"UartRecvThread-->run:"<<" !!!";
        if (m_serialRecv->isOpen())
        {
            while (m_serialRecv->waitForReadyRead(-1))
            {
                const QByteArray data = m_serialRecv->readAll();
                qDebug()<<"UartRecvThread-->readData:"<<data<<" !!!";
                const QString response = QString::fromUtf8(data);
                emit this->response(response);
            }
        }
    }
#endif
}

//! [4]
void UartRecvThread::runExample()
{
    bool currentPortNameChanged = false;

    m_mutex.lock();
    //! [4] //! [5]
    QString currentPortName;
    if (currentPortName != m_portName) {
        currentPortName = m_portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = m_waitTimeout;
    QString currentRequest = m_request;
    m_mutex.unlock();
    //! [5] //! [6]
    QSerialPort serial;

    if (currentPortName.isEmpty()) {
        emit error(tr("No port name specified"));
        return;
    }

    while (!m_quit) {
        //![6] //! [7]
        if (currentPortNameChanged) {
            serial.close();
            serial.setPortName(currentPortName);

            if (!serial.open(QIODevice::ReadWrite)) {
                emit error(tr("Can't open %1, error code %2")
                           .arg(m_portName).arg(serial.error()));
                return;
            }
        }
        //! [7] //! [8]
        // write request
        const QByteArray requestData = currentRequest.toUtf8();
        serial.write(requestData);
        if (serial.waitForBytesWritten(m_waitTimeout)) {
            //! [8] //! [10]
            // read response
            if (serial.waitForReadyRead(currentWaitTimeout)) {
                QByteArray responseData = serial.readAll();
                while (serial.waitForReadyRead(10))
                    responseData += serial.readAll();

                const QString response = QString::fromUtf8(responseData);
                //! [12]
                emit this->response(response);
                //! [10] //! [11] //! [12]
            } else {
                emit timeout(tr("Wait read response timeout %1")
                             .arg(QTime::currentTime().toString()));
            }
            //! [9] //! [11]
        } else {
            emit timeout(tr("Wait write request timeout %1")
                         .arg(QTime::currentTime().toString()));
        }
        //! [9]  //! [13]
        m_mutex.lock();
        m_cond.wait(&m_mutex);
        if (currentPortName != m_portName) {
            currentPortName = m_portName;
            currentPortNameChanged = true;
        } else {
            currentPortNameChanged = false;
        }
        currentWaitTimeout = m_waitTimeout;
        currentRequest = m_request;
        m_mutex.unlock();
    }
    //! [13]
}


int UartRecvThread::rpcProcess_sub1g(void)
{
    int32_t rpcLen, rpcTempLen, bytesRead, rpcBuffIdx;
    uint8_t retryAttempts = 0, rpcBuff[GH20_RX_FRAME_LEN_MAX];
    uint8_t frame_status;

    frame_status = 0;

    while(1)
    {
        if (!m_serialRecv->isOpen())
        {
            continue;
        }
        while(m_serialRecv->size())
        {
            logger(LOG_DEBUG, "<<<IN<<< frame_status=%d, size=%d", frame_status, m_serialRecv->size());
            switch (frame_status)
            {
            case 0:
                //read GH20_FM_HEAD: GH_PT_HEAD_0
                //bytesRead = rpcTransportRead_sub1g(&rpcBuff[0], 1);// TODO:
                bytesRead = m_serialRecv->read(reinterpret_cast<char*>(&rpcBuff[0]), 1);

                if (((unsigned char)rpcBuff[0] == GH_PT_HEAD_0) && (bytesRead == 1))
                {
                    frame_status = 1;
                }
                else
                {
                    logger(LOG_ERR, "no GH_PT_HEAD_0 read=%x", rpcBuff[0]);
                }
                break;
            case 1:
                //read GH20_FM_HEAD: GH_PT_HEAD_1
                //bytesRead = rpcTransportRead_sub1g(&rpcBuff[1], 1);// TODO:
                bytesRead = m_serialRecv->read(reinterpret_cast<char*>(&rpcBuff[1]), 1);
                if (((unsigned char)rpcBuff[1] == GH_PT_HEAD_1) && (bytesRead == 1))
                {
                    frame_status = 2;
                }
                else
                {
                    logger(LOG_ERR, "no GH_PT_HEAD_1 read=%x", rpcBuff[1]);
                }
                break;
            case 2:
            case 3:
                //read GH20_FM_TS
                //case 2: read GH20_FM_TS + GH20_FM_DIRT + GH20_FM_CMD + GH20_FM_LEN
                //case 3: read data + GH20_FM_CHECKSUM + GH20_FM_END
                if (2 == frame_status)
                {
                    rpcLen = GH20_FM_TS + GH20_FM_DIRT + GH20_FM_CMD + GH20_FM_LEN;
                    rpcBuffIdx = GH20_FM_HEAD;
                }
                rpcTempLen = rpcLen;
                while (rpcTempLen > 0)
                {
                    //bytesRead = rpcTransportRead_sub1g(&(rpcBuff[rpcBuffIdx]), rpcTempLen);// TODO:
                    bytesRead = m_serialRecv->read(reinterpret_cast<char*>(&rpcBuff[rpcBuffIdx]), rpcTempLen);
                    if (bytesRead > rpcTempLen)
                    {
                        logger(LOG_ERR,"frame_status=%d: rpcProcess: read of %d bytes failed - %s\n",
                               frame_status, rpcTempLen, strerror(errno));
                        // check whether retry limits has been reached
                        if (retryAttempts++ < 5)
                        {
                            // sleep for 10ms
                            usleep(10000);

                            // try again
                            bytesRead = 0;
                        }
                        else
                        {
                            // something went wrong, abort
                            logger(LOG_ERR, "frame_status=%d: rpcProcess: transport read failed too many times\n",
                                   frame_status);
                            return -1;
                        }
                    }
                    // update counters
                    if (rpcTempLen > bytesRead)
                    {
                        rpcTempLen -= bytesRead;
                    }
                    else
                    {
                        rpcTempLen = 0;
                    }
                    rpcBuffIdx += bytesRead;
                }
                if (2 == frame_status)
                {
                    if ((unsigned char)rpcBuff[GH20_FRAM_LEN_INDEX] < GH20_RX_FRAME_WAVE_LEN_MAX)
                    {
                        frame_status = 3;
                        rpcLen = (unsigned char)rpcBuff[GH20_FRAM_LEN_INDEX] + GH20_FM_CHECKSUM + GH20_FM_END;
                        rpcBuffIdx = GH20_FRAM_LEN_INDEX + GH20_FM_LEN;
                    }
                }
                else
                {
                    //read frame ok, add to queue
                    if (check_frame_valid((uint8_t *)rpcBuff) > 0)
                    {
                        logger(LOG_DEBUG, "<<<IN<<< data valid ok");
                        //llq_add(m_pllq, (char*) &rpcBuff[0], rpcBuff[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN, 0);
                        return 0;
                    }
                    else
                    {
                        logger(LOG_DEBUG, "<<<IN<<< data not valid!!");
                        print_data_group((uint8_t *)rpcBuff, rpcBuff[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN);
                        printf("--------\n");
                        return -1;
                    }
                }
                break;
            }
        }
    }
    return -1;
}

void UartRecvThread::updataInfo(QSerialPort *serial)
{
    if (this->isRunning())
    {
        this->terminate();
    }
    m_serialRecv = serial;
    if (this->isRunning())
    {
        this->start();
    }
}


