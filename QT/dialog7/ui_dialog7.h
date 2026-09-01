/********************************************************************************
** Form generated from reading UI file 'dialog7.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG7_H
#define UI_DIALOG7_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_dialog7
{
public:

    void setupUi(QDialog *dialog7)
    {
        if (dialog7->objectName().isEmpty())
            dialog7->setObjectName(QStringLiteral("dialog7"));
        dialog7->resize(400, 300);

        retranslateUi(dialog7);

        QMetaObject::connectSlotsByName(dialog7);
    } // setupUi

    void retranslateUi(QDialog *dialog7)
    {
        dialog7->setWindowTitle(QApplication::translate("dialog7", "dialog7", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog7: public Ui_dialog7 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG7_H
