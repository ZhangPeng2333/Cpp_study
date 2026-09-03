#ifndef DIALOG9_H
#define DIALOG9_H

#include <QDialog>


namespace Ui {
class dialog9;
}

class dialog9 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog9(QWidget *parent = 0);
    ~dialog9();

private:
    Ui::dialog9 *ui;
    QPixmap m_pixmap;

protected:
    void paintEvent(QPaintEvent *);
    void keyReleaseEvent(QKeyEvent * event);

};

#endif // DIALOG9_H
