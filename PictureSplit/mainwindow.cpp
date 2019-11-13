#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    , m_nOrderRule(EO_H)
    , m_nBorder(0)
{
    ui->setupUi(this);
    connect(ui->menuFile, SIGNAL(triggered(QAction*)), this, SLOT(menuFileTriggered(QAction*)));
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onBtnOkClick()));
    QButtonGroup *operatingModeGroup = new QButtonGroup(this);
    operatingModeGroup->addButton(ui->radioButtonH, EO_H);
    operatingModeGroup->addButton(ui->radioButtonV, EO_V);
    connect(operatingModeGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(onGroupTriggered(int,bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuFileTriggered(QAction *action)
{
    if (action == ui->actionOpenDir)
    {

        m_strDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../",
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    }
    else if (action == ui->actionOpenFile)
    {
        m_strFile = QFileDialog::getOpenFileName(this, tr("Open file"));
        if (!m_strFile.isEmpty())
        {
            if (!pixSrc.load(m_strFile))
            {
                qDebug() << "load file fail:" + m_strFile;
            }
            qDebug() << "pic width:"<< pixSrc.size().width()<< "  pic height:" << pixSrc.size().height();
            ui->labelDisplayer->setFixedSize(pixSrc.size());
            ui->labelDisplayer->setPixmap(pixSrc);
        }
    }
}

void MainWindow::onBtnOkClick()
{
    // 以像素表示
    QFileInfo fileInfo(m_strFile);
    QString fileBaseName = fileInfo.baseName();
    qDebug() << fileBaseName;
    m_nBorder = ui->leItemMargin->text().toInt();
    // 单元像素
    int nItemWidth = ui->leWidth->text().isEmpty() ? 32 : ui->leWidth->text().toInt();
    int nItemHeight = ui->leHeight->text().isEmpty() ? 32 : ui->leHeight->text().toInt();
    qDebug() << "nItemWidth" << nItemWidth << "nItemHeight" << nItemHeight;

    // 单元数量
    int nItemRowTotal = ui->labelDisplayer->width() / nItemWidth;
    int nItemColumnTotal = ui->labelDisplayer->height() / nItemHeight;

    if (m_nOrderRule == EO_H)
    {
        for (int i = 0; i < nItemRowTotal; ++i)
        {
            int nX = ui->labelDisplayer->rect().left() + i * nItemWidth + m_nBorder * (i + 1);
            for (int j = 0; j < nItemColumnTotal; ++j)
            {

                int nY = ui->labelDisplayer->rect().top() + j * nItemHeight+ m_nBorder * (j + 1);
                QRect rectItem( nX, nY, nItemWidth, nItemHeight);

                //lstRectItem.append(rectItem);
                QPixmap pix = pixSrc.copy(rectItem);
                //剪切出的图片的保存地址
                pix.save(fileBaseName + "_" + QString::number(i) + "_" + QString::number(j) + ".png","png");

            }
        }
    }
    else
    {
        for (int i=0; i < nItemRowTotal; ++i)
        {
            for (int j=0; j < nItemColumnTotal; ++j)
            {
                // 即旋转90度切分单元，但图像正立
                int nX = ui->labelDisplayer->rect().left() + j * nItemWidth + m_nBorder * (j + 1);
                int nY = ui->labelDisplayer->rect().top() + i * nItemHeight + m_nBorder * (i + 1);
                QRect rectItem( nX, nY, nItemWidth, nItemHeight);

                //lstRectItem.append(rectItem);
                QPixmap pix = pixSrc.copy(rectItem);
                //剪切出的图片的保存地址
                pix.save(fileBaseName + "_" + QString::number(i) + "_" + QString::number(j) + ".png","png");
            }
        }
    }
    qDebug() << "finish";
}

void MainWindow::onGroupTriggered(int id, bool checked)
{
    m_nOrderRule = id;
}


QImage MainWindow::mergeImageH(vector <QImage > vecImages)
{
    int image_width=0;
    int max_height = 0;
    vector <QImage > ::iterator it;
    for(it = vecImages.begin();it!=vecImages.end();++it)
    {
        int width = (*it).width();
        image_width += width;
        if((*it).height()>max_height)
        {
            max_height =(*it).height();
        }
    }
    QImage result_image_h(image_width,max_height,QImage::Format_RGB32);
    result_image_h.fill(Qt::white);
    QPainter painter_h;
    painter_h.begin(&result_image_h);
    int x_number=0;
    for(it = vecImages.begin();it!=vecImages.end();++it)
    {
        painter_h.drawImage(x_number,0,(*it));
        x_number += (*it).width();
    }
    painter_h.end();
    QString name = image_output_path_.append("/").append(merge_output_filename_).append(".").append(convert_format_);
    result_image_h.save(name,convert_format_.toAscii().data());
    return result_image_h;
}


QImage MainWindow::MergeImageV(vector <QImage > vecImages)
{
    int max_width = 0;
    int image_height=0;
    vector <QImage > ::iterator it;
    for(it = vecImages.begin();it!=vecImages.end();++it)
    {
        int height = (*it).height();
        image_height += height;
        if((*it).width() > max_width)
        {
            max_width =(*it).width();
        }
    }

    QImage result_image_v(max_width,image_height,QImage::Format_RGB32);
    result_image_v.fill(Qt::white);
    QPainter painter_v;
    painter_v.begin(&result_image_v);
    int y_number=0;
    for(it = vecImages.begin();it!=vecImages.end();++it)
    {
        painter_v.drawImage(0,y_number,(*it));
        y_number += (*it).height();
    }
    painter_v.end();
    QString name = image_output_path_.append("/").append(merge_output_filename_).append(".").append(convert_format_);
    emit startConvertMove(1,1);
    result_image_v.save(name,convert_format_.toAscii().data());
    return result_image_v;
}
