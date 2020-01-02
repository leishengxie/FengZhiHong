#ifndef QMYBUTTON_H
#define QMYBUTTON_H
#include <QPushButton>

class QMyButton:public QPushButton
{
    Q_OBJECT
public:
    explicit QMyButton(const QString &text, QWidget *parent=0);

protected:

private:
};


#endif // QMYBUTTON_H
