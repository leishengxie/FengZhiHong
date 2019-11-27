#ifndef JOKEBOOKWIDGET_H
#define JOKEBOOKWIDGET_H

#include <QWidget>

namespace Ui {
class CJokebookWidget;
}

class CJokebookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CJokebookWidget(QWidget *parent = 0);
    ~CJokebookWidget();

private:
    Ui::CJokebookWidget *ui;
};

#endif // JOKEBOOKWIDGET_H
