/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButtonConn;
    QPushButton *pushButtonDisconn;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(816, 511);
        pushButtonConn = new QPushButton(Widget);
        pushButtonConn->setObjectName(QString::fromUtf8("pushButtonConn"));
        pushButtonConn->setGeometry(QRect(110, 290, 93, 28));
        pushButtonDisconn = new QPushButton(Widget);
        pushButtonDisconn->setObjectName(QString::fromUtf8("pushButtonDisconn"));
        pushButtonDisconn->setGeometry(QRect(420, 290, 93, 28));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 40, 401, 51));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 150, 72, 15));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButtonConn->setText(QApplication::translate("Widget", "\345\205\263\350\201\224", nullptr));
        pushButtonDisconn->setText(QApplication::translate("Widget", "\350\247\243\351\231\244\345\205\263\350\201\224", nullptr));
        label->setText(QApplication::translate("Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
