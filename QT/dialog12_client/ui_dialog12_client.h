/********************************************************************************
** Form generated from reading UI file 'dialog12_client.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG12_CLIENT_H
#define UI_DIALOG12_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dialog12_client
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;

    void setupUi(QDialog *dialog12_client)
    {
        if (dialog12_client->objectName().isEmpty())
            dialog12_client->setObjectName(QStringLiteral("dialog12_client"));
        dialog12_client->resize(635, 198);
        verticalLayout = new QVBoxLayout(dialog12_client);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(dialog12_client);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(dialog12_client);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(dialog12_client);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBox = new QSpinBox(dialog12_client);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy1);
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox->setMinimum(1024);
        spinBox->setMaximum(65535);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBox);


        horizontalLayout->addLayout(formLayout);

        pushButton = new QPushButton(dialog12_client);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_2 = new QLineEdit(dialog12_client);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_2);

        label_3 = new QLabel(dialog12_client);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font: 75 16pt \"Arial\";"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_3 = new QLineEdit(dialog12_client);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_2->addWidget(lineEdit_3);

        pushButton_2 = new QPushButton(dialog12_client);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(dialog12_client);

        QMetaObject::connectSlotsByName(dialog12_client);
    } // setupUi

    void retranslateUi(QDialog *dialog12_client)
    {
        dialog12_client->setWindowTitle(QApplication::translate("dialog12_client", "dialog12_client", 0));
        label->setText(QApplication::translate("dialog12_client", "IP", 0));
        label_2->setText(QApplication::translate("dialog12_client", "Port", 0));
        pushButton->setText(QApplication::translate("dialog12_client", "Connect", 0));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("dialog12_client", "\346\230\265\347\247\260", 0));
        label_3->setText(QApplication::translate("dialog12_client", ":", 0));
        lineEdit_3->setPlaceholderText(QApplication::translate("dialog12_client", "\350\257\267\350\276\223\345\205\245\350\246\201\345\217\221\351\200\201\347\232\204\346\266\210\346\201\257", 0));
        pushButton_2->setText(QApplication::translate("dialog12_client", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class dialog12_client: public Ui_dialog12_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG12_CLIENT_H
