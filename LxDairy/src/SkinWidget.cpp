#include "SkinWidget.h"
#include "ui_SkinWidget.h"

#include <QApplication>
#include <QListWidgetItem>
#include <QFile>
#include <QSettings>
#include "LQt.h"

#include "LMapleLeafStyle.h"
#include "DairyAppStation.h"

static QString s_aSkin[] =
{
    ":/css/black.css",
    ":/css/blue.css",
    ":/css/gray.css",
    ":/css/navy.css"
};

static const QString s_arrImgBg[] =
{
    ":/img/bg/bg_green_natural.jpg",
    ":/img/bg/bg_quiet.jpg",
    ":/img/bg/bg_scholar_spirit.jpg",
    ":/img/bg/bg_maple_leaf.jpg"
};



CSkinWidget::CSkinWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CSkinWidget)
    , m_unIndexSave(0)
    , m_unIndexCur(0)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal, true); // 设置模态
    //setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(slot_saveCurrentSet()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_list_clicked(QListWidgetItem*)));
    CLQt::moveToDeskCenter(this);

    //    QPalette pal;
    //    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/img/bg/1.jpg").scaled(size())));
    //    setPalette(pal);

}

CSkinWidget::~CSkinWidget()
{
    delete ui;
}


//////////static func ///////////
void CSkinWidget::loadQssStyle()
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    uint unIndex = conf.value("skin_index", 0).toUInt();
    setSkin(unIndex);

}


void CSkinWidget::setSkin(uint nSkinIndex)
{
    if (nSkinIndex > 7)
    {
        return;
    }
    if (nSkinIndex > 3)
    {

        //QApplication::setStyle(new CCustomStyle());
        qApp->setStyleSheet("");
        QApplication::setStyle(new CLMapleLeafStyle());
        // QApplication::setStyle(new QProxyStyle());
        QPixmap pixmap(s_arrImgBg[nSkinIndex - 4]);
        CDairyAppStation::getInstance()->bgPixmapChanged(pixmap);
        return;
    }
    setQssStyle(s_aSkin[nSkinIndex]);
}

void CSkinWidget::setQssStyle(const QString & stylefilePath)
{
    QFile file(stylefilePath);
    bool bOk = file.open(QFile::ReadOnly);
    if (!bOk)
    {
        return;
    }
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
    file.close();
}

QPixmap CSkinWidget::currentBackgroundPixmap()
{
    if (unIndex > 3 && unIndex < 8)
    {
    s_pixmap.load(s_arrImgBg[unIndex - 4]);
    }
}


////////////non - static /////////
/// \brief CSkinWidget::slot_cancelCurrentSet
///
void CSkinWidget::slot_cancelCurrentSet()
{
    setSkin(m_unIndexSave);
}

void CSkinWidget::slot_saveCurrentSet()
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    conf.setValue("skin_index", m_unIndexCur);
    m_unIndexSave = m_unIndexCur;
    close();
}

void CSkinWidget::slot_list_clicked(QListWidgetItem* pItem)
{
    m_unIndexCur = ui->listWidget->currentRow();
    setSkin(m_unIndexCur);
}

void CSkinWidget::closeEvent(QCloseEvent* event)
{
    slot_cancelCurrentSet();
    QWidget::closeEvent(event);
}
