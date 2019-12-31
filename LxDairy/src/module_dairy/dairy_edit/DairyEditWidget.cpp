#include "DairyEditWidget.h"
#include "ui_DairyEditWidget.h"
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include "SqlOperate.h"

#include "dairy_tag/DairyTagListModel.h"
#include "DairyApp.h"



CDairyEditWidget::CDairyEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{
    init();
}

CDairyEditWidget::CDairyEditWidget(CDairy dairy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDairyEditWidget)
{
    init();

    setWindowTitle(dairy.getTitle());

    QString strDateTime = dairy.getDateTime();
    QDateTime datetime = QDateTime::fromString(strDateTime, FORMAT_DATETIME);
    QString strDateTimeDisplay = datetime.toString(FORMAT_DATETIME_DISPLAYER);
    did = dairy.getDid();
    ui->comboBoxWeather->setCurrentText(dairy.getWeather());
    ui->comboBoxTag->setCurrentText(dairy.getTag());
    ui->labelDateTime->setText(strDateTimeDisplay);
    ui->leTitle->setText(dairy.getTitle());
    ui->dairyEdit->setPlainText(dairy.getContent());


}

CDairyEditWidget::~CDairyEditWidget()
{
    delete ui;
}

void CDairyEditWidget::init()
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    // 获取并显示标签
    ui->comboBoxTag->clear();
    ui->comboBoxTag->addItems(CDairyTagListModel::listSysDefaultDairyTagNames());

}

void CDairyEditWidget::onSave()
{
    QString strDateTimeDisplayer = ui->labelDateTime->text();
    QDateTime datetime = QDateTime::fromString(strDateTimeDisplayer, FORMAT_DATETIME_DISPLAYER);
    QString strDateTime = datetime.toString(FORMAT_DATETIME);

    CDairy dairy;
    CDairy dairySaved;
    dairy.setDid(did);
    dairy.setUid(CDairyApp::userInfo().uid);
    dairy.setTitle(ui->leTitle->text());
    dairy.setDateTime(strDateTime);
    dairy.setTag(ui->comboBoxTag->currentText());
    dairy.setWeather(ui->comboBoxWeather->currentText());
    dairy.setContent(ui->dairyEdit->toPlainText()); //toPlainText 去除textEdit当中的纯文本
    QApplication::setOverrideCursor(Qt::WaitCursor);//设置整个应用程序的光标形状为等待形状，因为如果文件的内容非常多时可以提醒用户
    QString strError;
    if (!CSqlOperate::saveDairy(dairy, dairySaved, strError))
    {
        QMessageBox::warning(this, "save error", strError);
    }
    else
    {
        emit saveDairyfinished(dairy, dairySaved);
        did = dairySaved.getDid();
        setWindowTitle(dairySaved.getTitle());
        ui->dairyEdit->document()->setModified(false);
    }
    QApplication::restoreOverrideCursor();//恢复开始时的光标状态


}

CDairyEdit *CDairyEditWidget::dairyEdit()
{
    return ui->dairyEdit;
}

void CDairyEditWidget::closeEvent(QCloseEvent *event)
{
    //qDebug() << parent() << "调用了子控件的close";
    if(ui->dairyEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("the File is changed");
        // 显示的文本
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        // 设置默认选中button
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Save:
            onSave();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            event->ignore();
            return;
        default:
            break;
        }
    }
    event->accept();
}

void CDairyEditWidget::onCopy()
{
    ui->dairyEdit->copy();
}




