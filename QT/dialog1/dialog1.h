#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateButtonMaxSize();

    // 控件指针
    QLineEdit   *m_username;
    QLineEdit   *m_password;
    QPushButton *m_login;
    QPushButton *m_signup;
};

#endif // DIALOG1_H
