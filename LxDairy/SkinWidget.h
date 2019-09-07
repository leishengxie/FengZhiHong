#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class CSkinWidget;
}

class CSkinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CSkinWidget(QWidget *parent = 0);
    ~CSkinWidget();

private slots:
    void slot_cancel();
    void slot_ok();
    void slot_list_clicked(QListWidgetItem *pItem);

private:
    Ui::CSkinWidget *ui;
};

#endif // SKINWIDGET_H
