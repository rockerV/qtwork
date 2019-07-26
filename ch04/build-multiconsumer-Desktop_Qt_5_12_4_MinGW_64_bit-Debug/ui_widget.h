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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButtonAnderson;
    QPushButton *pushButtonBruce;
    QPushButton *pushButtonCastiel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 300);
        pushButtonAnderson = new QPushButton(Widget);
        pushButtonAnderson->setObjectName(QString::fromUtf8("pushButtonAnderson"));
        pushButtonAnderson->setGeometry(QRect(100, 30, 93, 28));
        pushButtonBruce = new QPushButton(Widget);
        pushButtonBruce->setObjectName(QString::fromUtf8("pushButtonBruce"));
        pushButtonBruce->setGeometry(QRect(110, 90, 93, 28));
        pushButtonCastiel = new QPushButton(Widget);
        pushButtonCastiel->setObjectName(QString::fromUtf8("pushButtonCastiel"));
        pushButtonCastiel->setGeometry(QRect(110, 150, 93, 28));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButtonAnderson->setText(QApplication::translate("Widget", "Anderson", nullptr));
        pushButtonBruce->setText(QApplication::translate("Widget", "Bruce", nullptr));
        pushButtonCastiel->setText(QApplication::translate("Widget", "Castiel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
