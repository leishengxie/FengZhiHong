#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class CLoginWidget;
}

class CLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CLoginWidget(QWidget *parent = 0);
    ~CLoginWidget();

public slots:
    void onBgPixmapChanged(const QPixmap & pixmap);



private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void on_ckboxRememberUserName_clicked(bool checked);

    void on_ckboxRememberPasswd_clicked(bool checked);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::CLoginWidget *ui;

    // 背景图片
    QPixmap m_pixBg;
};

#endif // LOGINWIDGET_H
