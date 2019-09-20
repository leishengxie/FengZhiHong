#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSharedPointer>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSharedPointer<T_custom> p1(new T_custom(1));
    QSharedPointer<T_custom> p2(new T_custom(5));
    QSharedPointer<T_custom> p3(new T_custom(1));
    m_setCustom.insert(p1);
    m_setCustom.insert(p2);
    m_setCustom.insert(p3);
    qDebug() << m_setCustom.size();

    T_custom t1(1);
    T_custom t2(5);
    T_custom t3(1);
    m_setCustomObj.insert(t1);
    m_setCustomObj.insert(t2);
    m_setCustomObj.insert(t3);
    qDebug() << m_setCustomObj.size();

}

MainWindow::~MainWindow()
{
    delete ui;
}

uint qHash(const QSharedPointer<T_custom> key, uint seed)
{
    return key->a;
}

uint qHash(const T_custom key, uint seed)
{
    return key.a;
}
