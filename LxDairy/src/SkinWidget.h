#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QWidget>
class QListWidgetItem;

namespace Ui {
class CSkinWidget;
}

///
/// \brief The CSkinNotifyCenter class
///
class CSkinNotifyCenter
{

};

///
/// \brief The CSkinWidget class: the skin select
/// 皮肤管理界面
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
    static QPixmap currentBackgroundPixmap();

signals:


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_cancelCurrentSet();
    void slot_saveCurrentSet();
    void slot_list_clicked(QListWidgetItem *pItem);


private:
    Ui::CSkinWidget *ui;
    static uint s_unIndexSave;
    uint m_unIndexCur;
};

#endif // SKINWIDGET_H
