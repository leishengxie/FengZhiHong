#ifndef CCHESSWIDGET_H
#define CCHESSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CGobangGameWidget; }
QT_END_NAMESPACE

class CGobangGameWidget : public QWidget
{
    Q_OBJECT

public:
    CGobangGameWidget(QWidget *parent = nullptr);
    ~CGobangGameWidget();

private:
    Ui::CGobangGameWidget *ui;
};
#endif // CCHESSWIDGET_H
