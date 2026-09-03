/********************************************************************************
** Form generated from reading UI file 'dialog9.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG9_H
#define UI_DIALOG9_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_dialog9
{
public:
    QProgressBar *progressBar;

    void setupUi(QDialog *dialog9)
    {
        if (dialog9->objectName().isEmpty())
            dialog9->setObjectName(QStringLiteral("dialog9"));
        dialog9->resize(761, 567);
        progressBar = new QProgressBar(dialog9);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(50, 250, 691, 41));
        progressBar->setValue(24);

        retranslateUi(dialog9);

        QMetaObject::connectSlotsByName(dialog9);
    } // setupUi

    void retranslateUi(QDialog *dialog9)
    {
        dialog9->setWindowTitle(QApplication::translate("dialog9", "dialog9", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog9: public Ui_dialog9 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG9_H
