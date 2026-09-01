#ifndef SLIDER_DIALOGWORK1_H
#define SLIDER_DIALOGWORK1_H

#include <QDialog>
#include<QSlider>
#include<iostream>
namespace Ui {
class slider_dialogWork1;
}

class slider_dialogWork1 : public QDialog
{
    Q_OBJECT

public:
    explicit slider_dialogWork1(QWidget *parent = 0);
    ~slider_dialogWork1();

private:
    Ui::slider_dialogWork1 *ui;
    QDialog* clddlg = NULL;
    QDialog* frddlg= NULL;
    QSlider* child_slider= NULL;
    QSlider* friend_slider= NULL;

private slots:
    void createChildSlot();
    void createFriendSlot();
    void changeFandCSliderValue(int value);
    void changeMainSliderValue(int value);
};

#endif // SLIDER_DIALOGWORK1_H
