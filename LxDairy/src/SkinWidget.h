#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <list>
#include <QWidget>
class QListWidgetItem;

using namespace std;
namespace Ui {
class CSkinWidget;
}

/// 为了降偶，使用观察者模式替代了原来的CDairyAppStation
class ISkinListenner
{
public:
    ISkinListenner();
    ~ISkinListenner();

    virtual void requreRefrshBackground(const QPixmap& pixmpap) = 0;
};

class ISkinNotifier
{
public:
    ISkinNotifier();
    ~ISkinNotifier();

public:
    virtual void addListenner(ISkinListenner* listenner) = 0;
    virtual void removeListenner(ISkinListenner* listenner) = 0;
    //virtual void notify() = 0;
    virtual void notityBackgroundChanged(const QPixmap& pixmpap);

};

///
/// \brief The CSkinNotifyCenter class
///
class CSkinNotifyCenter : public ISkinNotifier
{

public:
    static CSkinNotifyCenter* getInstance();

    virtual void addListenner(ISkinListenner* listenner)
    {
        m_listenners.push_back(listenner);
    }

    virtual void removeListenner(ISkinListenner* listenner)
    {
        //if contains();
        m_listenners.remove(listenner);
        //delete listenner;
    }

    virtual notityBackgroundChanged(const QPixmap& pixmpap)
    {
        list <ISkinListenner*> ::iterator it = m_listenners.begin();
        for (; it != m_listenners.end(); ++it)
        {
            (*it)->requreRefrshBackground(pixmpap);
        }
    }

private:
    static CSkinNotifyCenter* m_pLNotificationCenter;

private:
    list<ISkinListenner*> m_listenners;
};

///
/// \brief The CSkinMemento class 皮肤选择备忘录
/// 主要争对用户选择皮肤后显示当前皮肤，点击取消按钮需要恢复先前的
///  备忘录模式
///
class CSkinMemento
{
public:
    CSkinMemento(){}
    CSkinMemento(uint unIndex)
        : m_unIndex(unIndex)
    {

    }

    uint getIndex()
    {
        return m_unIndex;
    }

private:
    // 需要备忘的数据
    uint m_unIndex;
};

///
/// \brief The CSkinMementoCareTaker class 皮肤选择备忘录管理者
///
class CSkinMementoCareTaker
{
    void save(const CSkinMemento & skinMemento)
    {
        m_skinMemento = skinMemento;
    }

    CSkinMemento load() const
    {
        return m_skinMemento;
    }
private:
    CSkinMemento m_skinMemento; //
    //list<CSkinMemento> m_lstSkinMemento;    // 如果管理多个存档，可用列表
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

    CSkinMemento saveIndexToMemento() const
    {
        CSkinMemento skinMemento(m_unIndexCur);
        return skinMemento;
    }

    void getIndexFromMemento(const CSkinMemento & skinMemento)
    {
        m_unIndexCur = skinMemento.getIndex();
    }

signals:


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_cancelCurrentSet();
    void slot_saveCurrentSet();
    void slot_list_clicked(QListWidgetItem *pItem);


private:
    Ui::CSkinWidget *ui;

    // 暂时不换成备忘录模式，因为当前存储的只有index,如果恢复的数据比较多或多个存档s_unIndexSave可换成CSkinMementoCareTaker
    static uint s_unIndexSave;

    uint m_unIndexCur;
};

#endif // SKINWIDGET_H
