/********************************************************************************
** Form generated from reading UI file 'dialog4.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG4_H
#define UI_DIALOG4_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog4
{
public:
    QWidget *centralWidget;
    QSpinBox *spinBox;
    QDial *dial;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QSlider *horizontalSlider;
    QSlider *verticalSlider;
    QProgressBar *progressBar;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dialog4)
    {
        if (dialog4->objectName().isEmpty())
            dialog4->setObjectName(QStringLiteral("dialog4"));
        dialog4->resize(881, 734);
        centralWidget = new QWidget(dialog4);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(90, 380, 49, 25));
        dial = new QDial(centralWidget);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(0, 0, 171, 171));
        dial->setWrapping(true);
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(230, 330, 160, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(300, 410, 16, 160));
        verticalScrollBar->setOrientation(Qt::Vertical);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(50, 460, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(120, 500, 22, 160));
        verticalSlider->setOrientation(Qt::Vertical);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(230, 200, 120, 23));
        progressBar->setValue(24);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(60, 220, 113, 25));
        dialog4->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(dialog4);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 881, 30));
        dialog4->setMenuBar(menuBar);
        mainToolBar = new QToolBar(dialog4);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        dialog4->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(dialog4);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        dialog4->setStatusBar(statusBar);

        retranslateUi(dialog4);

        QMetaObject::connectSlotsByName(dialog4);
    } // setupUi

    void retranslateUi(QMainWindow *dialog4)
    {
        dialog4->setWindowTitle(QApplication::translate("dialog4", "dialog4", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog4: public Ui_dialog4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG4_H
