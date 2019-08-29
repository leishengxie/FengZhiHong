#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include"writerj.h"
#include<QTimer>
namespace Ui {
class DairyMainWindow;
}

class CDairyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDairyMainWindow(QWidget *parent = 0);
    ~CDairyMainWindow();
    void SetZhanghao(QString zhanghao);

private slots:
    void on_actionxieriji_triggered();
    void on_actionshuxin_triggered();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void timeroutshow();
    void on_actionpeizhi_triggered();
    void huoqu(QFont, QString , QString, QString, QString);
    void on_actionguanyu_triggered();

private:
    Ui::DairyMainWindow *ui;
    QTimer *timer;
    QFont font;
    QString pix;
    QString touxiang;
    QString wangming;
    QString geqian;

};

#endif // MAINWINDOW_H
