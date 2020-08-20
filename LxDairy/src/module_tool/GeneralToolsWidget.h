#ifndef GENERALTOOLSWIDGET_H
#define GENERALTOOLSWIDGET_H

#include <QWidget>

namespace Ui {
class CGeneralToolsWidget;
}

class CGeneralToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CGeneralToolsWidget(QWidget *parent = 0);
    ~CGeneralToolsWidget();

private slots:
    void on_listWidgetPrivate_clicked(const QModelIndex &index);

private:
    void loadPlugins();

private:
    Ui::CGeneralToolsWidget *ui;
};

#endif // GENERALTOOLSWIDGET_H
