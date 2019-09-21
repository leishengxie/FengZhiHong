#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QSharedPointer>

namespace Ui {
class MainWindow;
}

struct T_custom
{
    uint a;

    T_custom(uint a)
        : a(a)
    {

    }
    bool operator == (const T_custom &right) const
    {
        if (this->a == right.a)
        {
            return true;
        }
        return this->a < right.a;
    }

//    bool operator == (const QSharedPointer<T_custom> &right) const
//    {
//        if (this->a == right->a)
//        {
//            return true;
//        }
//        //return this->a < right->a;
//        return false;
//    }
};
bool operator==(QSharedPointer<T_custom> &c1, QSharedPointer<T_custom> &c2);


uint qHash(const QSharedPointer<T_custom> key, uint seed = 0);
uint qHash(const T_custom key, uint seed = 0);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSet<QSharedPointer<T_custom>> m_setCustom;
    QSet<T_custom> m_setCustomObj;
};

#endif // MAINWINDOW_H
