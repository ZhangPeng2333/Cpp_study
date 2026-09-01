/********************************************************************************
** Form generated from reading UI file 'slider_dialogwork1.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDER_DIALOGWORK1_H
#define UI_SLIDER_DIALOGWORK1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_slider_dialogWork1
{
public:
    QSlider *horizontalSlider;
    QPushButton *frdbtn;
    QPushButton *cldbtn;

    void setupUi(QDialog *slider_dialogWork1)
    {
        if (slider_dialogWork1->objectName().isEmpty())
            slider_dialogWork1->setObjectName(QStringLiteral("slider_dialogWork1"));
        slider_dialogWork1->resize(702, 520);
        horizontalSlider = new QSlider(slider_dialogWork1);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(150, 280, 300, 40));
        horizontalSlider->setOrientation(Qt::Horizontal);
        frdbtn = new QPushButton(slider_dialogWork1);
        frdbtn->setObjectName(QStringLiteral("frdbtn"));
        frdbtn->setGeometry(QRect(60, 60, 112, 34));
        cldbtn = new QPushButton(slider_dialogWork1);
        cldbtn->setObjectName(QStringLiteral("cldbtn"));
        cldbtn->setGeometry(QRect(60, 110, 112, 34));

        retranslateUi(slider_dialogWork1);

        QMetaObject::connectSlotsByName(slider_dialogWork1);
    } // setupUi

    void retranslateUi(QDialog *slider_dialogWork1)
    {
        slider_dialogWork1->setWindowTitle(QApplication::translate("slider_dialogWork1", "slider_dialogWork1", 0));
        frdbtn->setText(QApplication::translate("slider_dialogWork1", "PushButton", 0));
        cldbtn->setText(QApplication::translate("slider_dialogWork1", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class slider_dialogWork1: public Ui_slider_dialogWork1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDER_DIALOGWORK1_H
