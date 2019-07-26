#include "widget.h"
#include <QApplication>
#include "showvoid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    ShowVoid s; //②接收对象，有对应槽函数　RecvVoid()
    //③关联源头的信号和接收端的槽函数
    QObject::connect(&w, SIGNAL(SendVoid()), &s, SLOT(RecvVoid()));

    w.show();

    return a.exec();
}
