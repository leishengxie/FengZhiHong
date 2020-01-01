#include "SkinWidget.h"
#include "ui_SkinWidget.h"

#include <QApplication>
#include <QListWidgetItem>
#include <QFile>
#include <QSettings>
#include <QStyleFactory>
#include <QtDebug>
#include "LQt.h"

#include "LMapleLeafStyle.h"
#include "LGreenNaturalStyle.h"
#include "LQuietStyle.h"
#include "LScholarSpiritStyle.h"
#include "LNorwegianWoodStyle.h"
#include "LBronzeStyle.h"
#include "LDarkDevelopStyle.h"


#include "DairyAppStation.h"

// 皮肤对应的qss
static const char* s_aStyleSheet[] =
{
    ":/css/black.css",  // 0
    ":/css/blue.css",   // 1
    ":/css/gray.css",   // 2
    ":/css/navy.css",    // 3
    "",                 // 4
    "",                 // 5
    "",                 // 6
    "",                 // 7
    "",                 // 8
    "",                 // 9
    ""                  // 10
};

// 皮肤对应的背景图
static const char* s_arrImgBg[] =
{
    "",                                     // 0
    "",                                     // 1
    "",                                     // 2
    "",                                     // 3
    ":/img/bg/bg_green_natural.jpg",        // 4
    ":/img/bg/bg_quiet.jpg",                // 5
    ":/img/bg/bg_scholar_spirit.jpg",       // 6
    ":/img/bg/bg_maple_leaf.jpg",           // 7
    "",                                     // 8
    "",                                     // 9
    ""                                      // 10
};


uint CSkinWidget::s_unIndexSave = 0;

CSkinWidget::CSkinWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CSkinWidget)
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
    qDebug() << QStyleFactory::keys();
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    s_unIndexSave = conf.value("skin_index", 4).toUInt();
    setSkin(s_unIndexSave);

}


void CSkinWidget::setSkin(uint nSkinIndex)
{
    if (nSkinIndex > 10)
    {
        return;
    }

    // 设置style
    if (nSkinIndex == 4)
    {
        QApplication::setStyle(new CLGreenNaturalStyle());
    }
    else if (nSkinIndex == 5)
    {
        QApplication::setStyle(new CLQuietStyle());
    }
    else if (nSkinIndex == 6)
    {
        QApplication::setStyle(new CLScholarSpiritStyle());
    }
    else if (nSkinIndex == 7)
    {
        QApplication::setStyle(new CLMapleLeafStyle());
        //QCursor cursor(QPixmap(":/img/cursor.png"));
        //setCursor(cursor);
    }
    else if (nSkinIndex == 8)
    {
        QApplication::setStyle(new CLNorwegianWoodStyle());
    }
    else if (nSkinIndex == 9)
    {
        QApplication::setStyle(new CLBronzeStyle());
    }
    else if (nSkinIndex == 10)
    {
        QApplication::setStyle(new CLDarkDevelopStyle());
    }
    else
    {
        QApplication::setStyle(QStyleFactory::create("windowsvista"));
    }

    // 设置qss
    setQssStyle(s_aStyleSheet[nSkinIndex]);

    // 设置背景图
    QPixmap pixmap;
    if (!QString(s_arrImgBg[nSkinIndex]).isEmpty())
    {
        pixmap.load(s_arrImgBg[nSkinIndex]);
    }
    CDairyAppStation::getInstance()->bgPixmapChanged(pixmap);

}

void CSkinWidget::setQssStyle(const QString & stylefilePath)
{
    if (stylefilePath.isEmpty())
    {
        qApp->setStyleSheet("");
        return;
    }

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
    QPixmap pixmap;
    if (!QString(s_arrImgBg[s_unIndexSave]).isEmpty())
    {
        pixmap.load(s_arrImgBg[s_unIndexSave]);
    }
    return pixmap;
}


////////////non - static /////////
/// \brief CSkinWidget::slot_cancelCurrentSet
///
void CSkinWidget::slot_cancelCurrentSet()
{
    setSkin(s_unIndexSave);
}

void CSkinWidget::slot_saveCurrentSet()
{
    QSettings conf("conf.ini", QSettings::IniFormat);
    conf.beginGroup("user");
    conf.setValue("skin_index", m_unIndexCur);
    s_unIndexSave = m_unIndexCur;
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
