/********************************************************************************
** Form generated from reading UI file 'dialog6.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG6_H
#define UI_DIALOG6_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dialog6
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *dialog6)
    {
        if (dialog6->objectName().isEmpty())
            dialog6->setObjectName(QStringLiteral("dialog6"));
        dialog6->resize(400, 300);
        pushButton = new QPushButton(dialog6);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 150, 112, 34));

        retranslateUi(dialog6);

        QMetaObject::connectSlotsByName(dialog6);
    } // setupUi

    void retranslateUi(QDialog *dialog6)
    {
        dialog6->setWindowTitle(QApplication::translate("dialog6", "dialog6", 0));
        pushButton->setText(QApplication::translate("dialog6", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog6: public Ui_dialog6 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG6_H
