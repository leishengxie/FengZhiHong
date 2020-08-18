#include "echoplugin.h"
#include <QMessageBox>

const QString StrActionTitle = QObject::tr("插件");

EchoPlugin::EchoPlugin(QObject *parent) :
    QObject(parent),
	m_action(NULL)
{
	m_action = new QAction(StrActionTitle, this);
	//connect(m_action, &QAction::triggered, this, &EchoPlugin::slotTriggered);
}

void EchoPlugin::setCallBack(EMITSIGNAL)	//设置信息回调
{

}
void EchoPlugin::unload()
{

}
void EchoPlugin::updateFileIdFileInfo(const QString& fileId, const QString& md5, const QString& fileName, quint64 filesize)
{

}
bool EchoPlugin::isExistArchivingFile(const QString& fileId)		//归档中的的文件判断
{
	return false;
}
QWidget* EchoPlugin::createProcessCenter(QWidget* parent)
{
	return new QWidget(parent);
}
void EchoPlugin::login()
{
	
}

//QStringList EchoPlugin::CalculateType() const
//{
//    return QStringList()<< tr("Add")<<tr("Sub");
//}

//double EchoPlugin::Calculate(const QString &type, double xvar, double yvar)
//{
//    if(type == tr("Add"))
//        return xvar + yvar;
//    else if(type == tr("Sub"))
//        return xvar - yvar;
//    else return 0.0;
//}

QAction* EchoPlugin::getAciton()
{
	return m_action;
}

//void EchoPlugin::slot_languageChanged()
//{
//	m_action->setText(StrActionTitle);
//}

double EchoPlugin::func(const QString &type)
{
	return 0;
}

QStringList EchoPlugin::funcType() const
{
	return QStringList(); 
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(QMenuItemPluginLib, EchoPlugin)
#endif // QT_VERSION < 0x050000
