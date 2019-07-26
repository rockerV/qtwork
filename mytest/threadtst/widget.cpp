#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<"Widget!!!";
    m_pthread = new ThreadTst(this,3);
    connect(m_pthread, &ThreadTst::response, this, &Widget::showResponse);
    m_pthread->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showResponse(const QString &s)
{
    ui->label->setText(s);
}
