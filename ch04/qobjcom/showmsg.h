#ifndef SHOWMSG_H
#define SHOWMSG_H

#include <QObject>

class ShowMsg : public QObject
{
    Q_OBJECT
public:
    explicit ShowMsg(QObject *parent = nullptr);

signals:

public slots:
    //接收 SendMsg 信号的槽函数
    void RecvMsg(QString str);
};

#endif // SHOWMSG_H
