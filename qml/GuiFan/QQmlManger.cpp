#include "QQmlManger.h"

#include <QQuickView>
#include <QQuickItem>

#include <QDebug>

QQmlManger::QQmlManger(QObject* pParent)
    : QObject(pParent)
    , m_nNum(0)
{

}

void QQmlManger::onTool(E_ToolBtnType btnType)
{
    qDebug()<<"parent"<< this->parent();
    qDebug()<< "qml call C++ slots function type=" << btnType;
    m_pObjParent = this->parent();

    QObject *setButton =  m_pObjParent->findChild<QObject*>("qmlManger");
    QList<QObject*> lstChild = m_pObjParent->findChildren<QObject*>();
    for (int i = 0; i < lstChild.size(); ++i)
    {
        qDebug() << lstChild[i];
    }
    if(setButton!=NULL)
    {
        QObject::connect(setButton, SIGNAL(clicked()), this, SLOT(showText()));
        bool bRet = QMetaObject::invokeMethod(setButton, "setText", Q_ARG(QString, "world hello"));
        qDebug() << "call setText return - " << bRet;
        setButton->setProperty("width", 200);
        setButton->setProperty("text", QString(tr("hello,world,test")));
    }
    else
    {
        qDebug()<<"get button failed";
    }

    //i_setNum(50);
}

void QQmlManger::showText(QString text)
{
    qDebug() << text;
}

void QQmlManger::showText()
{
    qDebug() << "button click";
}

