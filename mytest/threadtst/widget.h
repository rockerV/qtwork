#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "threadtst.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    ThreadTst *m_pthread;



private slots:
    void showResponse(const QString &s);

};

#endif // WIDGET_H
