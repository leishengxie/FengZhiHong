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
private slots:
    void on_btnScreenshot_clicked();

private:
    Ui::COcrHandleWidget *ui;
};

#endif // _OCR_HANDLE_WIDGET_H
