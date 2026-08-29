#include "dialog1.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>

Dialog1::Dialog1(QWidget *parent)
    : QDialog(parent)
    , m_username(new QLineEdit(this))
    , m_password(new QLineEdit(this))
    , m_login(new QPushButton("登录", this))
    , m_signup(new QPushButton("注册", this))
{
    // ----- 窗口设置 -----
    setWindowTitle("登录");
    setMinimumSize(350, 220);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // ----- 输入框设置 -----
    m_password->setEchoMode(QLineEdit::Password);
    m_username->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_password->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // ----- 按钮设置 -----
    m_login->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_signup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_login->setMinimumSize(80, 30);
    m_signup->setMinimumSize(80, 30);

    // ----- 1. 表单布局（账号 / 密码）-----
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("账号:", m_username);
    formLayout->addRow("密码:", m_password);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // ----- 2. 按钮水平布局（按钮并排）-----
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_login);
    btnLayout->addWidget(m_signup);
    btnLayout->setSpacing(20);

    // ----- 3. 内容垂直布局（表单 + 按钮，紧凑排列）-----
    QVBoxLayout *contentLayout = new QVBoxLayout;
    contentLayout->addLayout(formLayout);
    contentLayout->addLayout(btnLayout);
    contentLayout->setSpacing(25);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    // 按钮不拉伸，紧贴表单下方
    contentLayout->setStretch(0, 1); // 表单拉伸
    contentLayout->setStretch(1, 0); // 按钮不拉伸

    // ----- 4. 水平居中容器（左右弹簧）-----
    QHBoxLayout *hCenterLayout = new QHBoxLayout;
    hCenterLayout->addStretch(1);
    hCenterLayout->addLayout(contentLayout, 0); // 内容不水平拉伸
    hCenterLayout->addStretch(1);
    hCenterLayout->setContentsMargins(40, 0, 40, 0);

    // ----- 5. 最终主布局（垂直居中，上下弹簧）-----
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // 直接设置给 this
    mainLayout->addStretch(1);               // 上弹簧
    mainLayout->addLayout(hCenterLayout, 0); // 水平居中容器不垂直拉伸
    mainLayout->addStretch(1);               // 下弹簧
    mainLayout->setContentsMargins(0, 30, 0, 30); // 上下边距

    // ----- 初始化按钮最大尺寸 -----
    updateButtonMaxSize();

    // ----- 应用样式表（美化）-----
    // 按钮样式（扁平，微软风格）
    QString buttonStyle =
        "QPushButton {"
        "    background-color: #f0f2f5;"
        "    border: 1px solid #d0d5dc;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    font-size: 10pt;"
        "    font-weight: normal;"
        "    color: #1a1a1a;"
        "}"
        "QPushButton:hover {"
        "    background-color: #e5e9ef;"
        "    border-color: #0078d4;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #ccd2db;"
        "    border-color: #005a9e;"
        "}";
    m_login->setStyleSheet(buttonStyle);
    m_signup->setStyleSheet(buttonStyle);

    // 输入框样式
    QString lineEditStyle =
        "QLineEdit {"
        "    border: 1px solid #d0d5dc;"
        "    border-radius: 3px;"
        "    padding: 6px 10px;"
        "    font-size: 10pt;"
        "    background-color: white;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #0078d4;"
        "    outline: none;"
        "}";
    m_username->setStyleSheet(lineEditStyle);
    m_password->setStyleSheet(lineEditStyle);
}

Dialog1::~Dialog1()
{
    // 所有子控件由 Qt 自动删除
}

void Dialog1::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    updateButtonMaxSize();
}

void Dialog1::updateButtonMaxSize()
{
    int w = width();
    int h = height();

    // 按钮最大宽度 = 窗口宽度的 1/5，但不超过 300，且不小于 100
    int maxW = qMin(w / 5, 300);
    maxW = qMax(maxW, 100);

    // 按钮最大高度 = 窗口高度的 1/8，但不超过 60，且不小于 30
    int maxH = qMin(h / 8, 100);
    maxH = qMax(maxH, 60);

    m_login->setMaximumSize(maxW, maxH);
    m_signup->setMaximumSize(maxW, maxH);
}
