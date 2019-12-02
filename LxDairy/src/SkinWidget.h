#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class CSkinWidget;
}

///
/// \brief The CSkinWidget class: the skin select
///
class CSkinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CSkinWidget(QWidget *parent = 0);
    ~CSkinWidget();
public:
    static void loadQssStyle();
    static void setSkin(uint nSkinIndex);
    static void setQssStyle(const QString &stylefilePath);
    static QPixmap s_pixmap;

signals:


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_cancelCurrentSet();
    void slot_saveCurrentSet();
    void slot_list_clicked(QListWidgetItem *pItem);


private:
    Ui::CSkinWidget *ui;
    uint m_unIndexSave;
    uint m_unIndexCur;
};

#endif // SKINWIDGET_H
