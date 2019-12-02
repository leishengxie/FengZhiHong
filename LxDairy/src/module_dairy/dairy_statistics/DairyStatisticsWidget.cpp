#include "DairyStatisticsWidget.h"
#include "ui_DairyStatisticsWidget.h"

#include <QtDebug>
#include "DairyStatisticsModel.h"
#include "DairyStatisticsDelegate.h"
#include "SqlOperate.h"

CDairyStatisticsWidget::CDairyStatisticsWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CDairyStatisticsWidget)
{
    ui->setupUi(this);
    // 初始化日记统计
    ui->btnOpenDairy->hide();

    CDairyStatisticsModel* pDairyStatisticsModel = new CDairyStatisticsModel(this);
    CDairyStatisticsDelegate* pDairyStatisticsDelegate = new CDairyStatisticsDelegate;
    ui->listViewStatistics->setModel(pDairyStatisticsModel);
    ui->listViewStatistics->setItemDelegate(pDairyStatisticsDelegate);
    connect(ui->listViewStatistics->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(slotSelectionChanged(QItemSelection, QItemSelection)));
}

CDairyStatisticsWidget::~CDairyStatisticsWidget()
{
    delete ui;
}

void CDairyStatisticsWidget::showStatisticsByTag(const QString & strTag)
{
    QString strQueryTag = ("全部日记" == strTag) ? "" : strTag;
    QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit("", strQueryTag);
    ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);

    ui->btnOpenDairy->hide();
    ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
    ui->labelTitle->setText(strTag);
}

void CDairyStatisticsWidget::showStatisticsByDate(const QString & strYear, const QString & strMonth)
{
    if (strMonth.isEmpty())
    {
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit(strYear);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
        ui->labelTitle->setText(QString("%1年的日记").arg(strYear));
    }
    else
    {
        QString strDate = QString("%1-%2").arg(strYear).arg(strMonth);
        QList<CDairy> lstDairy = CSqlOperate::getListDairyByLimit(strDate);
        ((CDairyStatisticsModel*)ui->listViewStatistics->model())->showDairyStatistics(lstDairy);
        ui->labelDairyTotal->setText(QString("(共%1项)").arg(lstDairy.size()));
        ui->labelTitle->setText(QString("%1年%2月的日记").arg(strYear).arg(strMonth));
    }

}

///
/// \brief CDairyMainWindow::slotSelectionChanged
/// \param selected 新选择的项目
/// \param deselected 刚刚被取消选择的项目
///
void CDairyStatisticsWidget::slotSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    Q_UNUSED(deselected)
    int nSelected = selected.indexes().size();
    qDebug() << "nSelected：" << nSelected;
    if (nSelected == 1)
    {
        ui->btnOpenDairy->show();
    }
    else
    {
        ui->btnOpenDairy->hide();
    }
    QItemSelectionModel* selectionModel = ui->listViewStatistics->selectionModel();
    QModelIndexList listSelected = selectionModel->selectedIndexes();
    qDebug() << QString("%1 item selected").arg(listSelected.size()); //不能用items,即使是没有选择的数目也不对
}



void CDairyStatisticsWidget::on_btnOpenDairy_clicked()
{
    QModelIndex indexCur = ui->listViewStatistics->currentIndex();
    T_DairyStatisticsItem tDairyStatisticsItem = qvariant_cast<T_DairyStatisticsItem>(indexCur.data());
    emit expandDairy(tDairyStatisticsItem.did);
}
