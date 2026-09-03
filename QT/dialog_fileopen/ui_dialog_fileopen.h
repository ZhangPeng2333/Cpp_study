/********************************************************************************
** Form generated from reading UI file 'dialog_fileopen.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FILEOPEN_H
#define UI_DIALOG_FILEOPEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_dialog_fileopen
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_save;
    QPushButton *pushButton_open;
    QTextBrowser *textBrowser_open;
    QProgressBar *progressBar;
    QTextBrowser *textBrowser_save;
    QPushButton *pushButton_copy;

    void setupUi(QDialog *dialog_fileopen)
    {
        if (dialog_fileopen->objectName().isEmpty())
            dialog_fileopen->setObjectName(QStringLiteral("dialog_fileopen"));
        dialog_fileopen->resize(882, 585);
        horizontalLayout_2 = new QHBoxLayout(dialog_fileopen);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_save = new QPushButton(dialog_fileopen);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        gridLayout->addWidget(pushButton_save, 0, 1, 1, 1);

        pushButton_open = new QPushButton(dialog_fileopen);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));

        gridLayout->addWidget(pushButton_open, 0, 0, 1, 1);

        textBrowser_open = new QTextBrowser(dialog_fileopen);
        textBrowser_open->setObjectName(QStringLiteral("textBrowser_open"));

        gridLayout->addWidget(textBrowser_open, 1, 0, 1, 1);

        progressBar = new QProgressBar(dialog_fileopen);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    background: #f0f0f0;          /* \346\234\252\345\241\253\345\205\205\351\203\250\345\210\206\347\232\204\350\203\214\346\231\257\350\211\262\357\274\210\346\265\205\347\201\260\357\274\211 */\n"
"    text-align: center;           /* \347\231\276\345\210\206\346\257\224\346\226\207\345\255\227\345\261\205\344\270\255 */\n"
"    color: #333;                  /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    padding: 1px;                 /* \347\273\231\345\235\227\347\225\231\350\276\271\350\267\235\357\274\214\350\247\206\350\247\211\346\233\264\350\210\222\346\234\215 */\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"                                 stop:0 rgb(96, 255, 176),\n"
"                                 stop:1 rgb(200, 220, 255));\n"
"    border-radius: 4px;           /* \344\270\216\346\225\264\344\275\223\345\234\206\350\247\222\345\214\271\351\205\215"
                        "\357\274\214\345\217\257\345\276\256\350\260\203 */\n"
"}"));
        progressBar->setValue(25);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        gridLayout->addWidget(progressBar, 3, 0, 1, 1);

        textBrowser_save = new QTextBrowser(dialog_fileopen);
        textBrowser_save->setObjectName(QStringLiteral("textBrowser_save"));

        gridLayout->addWidget(textBrowser_save, 1, 1, 1, 1);

        pushButton_copy = new QPushButton(dialog_fileopen);
        pushButton_copy->setObjectName(QStringLiteral("pushButton_copy"));

        gridLayout->addWidget(pushButton_copy, 3, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        retranslateUi(dialog_fileopen);

        QMetaObject::connectSlotsByName(dialog_fileopen);
    } // setupUi

    void retranslateUi(QDialog *dialog_fileopen)
    {
        dialog_fileopen->setWindowTitle(QApplication::translate("dialog_fileopen", "dialog_fileopen", 0));
        pushButton_save->setText(QApplication::translate("dialog_fileopen", "PushButton", 0));
        pushButton_open->setText(QApplication::translate("dialog_fileopen", "PushButton", 0));
        pushButton_copy->setText(QApplication::translate("dialog_fileopen", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog_fileopen: public Ui_dialog_fileopen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FILEOPEN_H
