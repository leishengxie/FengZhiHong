#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

using namespace std;
namespace Ui {
class MainWindow;
}

enum E_OrderRule
{
    EO_H,
    EO_V
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

QImage mergeImageH(vector <QImage > vecImages);
QImage MergeImageV(vector <QImage > vecImages);

private slots:
    void menuFileTriggered(QAction* action);
    void onBtnOkClick();
    void onGroupTriggered(int id, bool checked);

private:
    Ui::MainWindow *ui;
    QString m_strDir;
    QString m_strFile;
    QPixmap pixSrc;
    int m_nOrderRule;
    int m_nBorder; //原图中各个Item之间可能有边距
};

#endif // MAINWINDOW_H
