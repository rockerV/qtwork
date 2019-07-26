#include "showvoid.h"
#include <QMessageBox>

ShowVoid::ShowVoid(QObject *parent) : QObject(parent)
{

}
//槽函数，弹窗
void ShowVoid::RecvVoid()
{
    QMessageBox::information(NULL, tr("Show"), tr("Just void."));
}
