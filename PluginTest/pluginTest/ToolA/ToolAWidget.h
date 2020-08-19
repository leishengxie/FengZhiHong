#ifndef TOOLAWIDGET_H
#define TOOLAWIDGET_H

#include <QWidget>

namespace Ui {
class CToolAWidget;
}

class CToolAWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CToolAWidget(QWidget *parent = nullptr);
    ~CToolAWidget();

private:
    Ui::CToolAWidget *ui;
};

#endif // TOOLAWIDGET_H
