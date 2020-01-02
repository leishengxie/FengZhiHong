#include "QMybutton.h"

//MyButton::MyButton(QWidget *parent):QPushButton(parent)
QMyButton::QMyButton(const QString &text, QWidget *parent): QPushButton(text,parent)
{
    this->setStyleSheet("QPushButton{background-color:rgb(56,121,255)}");
    this->setFixedHeight(50);
    this->setFont(QFont("Times",20));
    this->setText(text);
}

