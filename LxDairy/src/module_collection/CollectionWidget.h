#ifndef COLLECTIONWIDGET_H
#define COLLECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class CCollectionWidget;
}

///
/// \brief The CCollectionWidget class  集-主界面
///
class CCollectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCollectionWidget(QWidget *parent = 0);
    ~CCollectionWidget();

private:
    Ui::CCollectionWidget *ui;
};

#endif // COLLECTIONWIDGET_H
