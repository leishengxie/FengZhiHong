#ifndef _OCR_HANDLE_WIDGET_H
#define _OCR_HANDLE_WIDGET_H

#include <QWidget>

namespace Ui {
class COcrHandleWidget;
}

class COcrHandleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit COcrHandleWidget(QWidget *parent = 0);
    ~COcrHandleWidget();

    QString picToWord(const QString &path);

signals:
    void finishOcr(const QString & strText);

public slots:
    void onFinishScreenshot(const QPixmap & pixmap);

private slots:
    void on_btnScreenshot_clicked();

    void on_btnSure_clicked();

private:
    Ui::COcrHandleWidget *ui;


};

#endif // _OCR_HANDLE_WIDGET_H
