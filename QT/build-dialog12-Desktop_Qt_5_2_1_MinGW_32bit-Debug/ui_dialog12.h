/********************************************************************************
** Form generated from reading UI file 'dialog12.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG12_H
#define UI_DIALOG12_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dialog12
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *dialog12)
    {
        if (dialog12->objectName().isEmpty())
            dialog12->setObjectName(QStringLiteral("dialog12"));
        dialog12->resize(714, 459);
        verticalLayout = new QVBoxLayout(dialog12);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(dialog12);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setStyleSheet(QLatin1String("font: 75 9pt \"Bookman Old Style\";\n"
"color: rgb(170, 170, 255);"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(dialog12);

        QMetaObject::connectSlotsByName(dialog12);
    } // setupUi

    void retranslateUi(QDialog *dialog12)
    {
        dialog12->setWindowTitle(QApplication::translate("dialog12", "dialog12", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog12: public Ui_dialog12 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG12_H
