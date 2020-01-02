#ifndef QQMLMANGER_H
#define QQMLMANGER_H

#include <QObject>
#include <QDebug>

class QQmlManger: public QObject
{

Q_OBJECT

    Q_ENUMS(E_ToolBtnType)          //这个将这个枚举类型声明到qml里面可用

    Q_PROPERTY(int num READ num WRITE setNum NOTIFY numChanged)
public:
    //直接调用函数，非槽函数
    Q_INVOKABLE void showText(QString text);
    Q_INVOKABLE void showText();
    QQmlManger(QObject* pParent = 0);


    enum E_ToolBtnType
    {
        LB_SET,
        LB_FILE
    };

public:
    int num()
    {
        return m_nNum;
    }

    void setNum(int num)
    {
        m_nNum = num;
    }
signals:
    void numChanged(int num);

public slots:
    void onTool(E_ToolBtnType btnType);
private:
     int m_nNum;
     QObject* m_pObjParent;
};

#endif // QQMLMANGER_H
