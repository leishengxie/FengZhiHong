#ifndef TOOLAWIDGET_H
#define TOOLAWIDGET_H

#include <QWidget>

namespace Ui {
class CToolAWidget;
}

class CToolBWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CToolBWidget(QWidget *parent = nullptr);
    ~CToolBWidget();

private:
    Ui::CToolAWidget *ui;
};

#endif // TOOLAWIDGET_H
