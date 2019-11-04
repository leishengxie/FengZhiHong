#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();

    void on_btnCreate_clicked();

private:
    Ui::MainWindow *ui;
    QStringList m_lstFlie;
    QFileInfoList m_lstFlieInfo;
};

#endif // MAINWINDOW_H
