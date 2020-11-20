#include "AccPasswdWidget.h"
#include "ui_AccPasswdWidget.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>

CAccPasswdWidget::CAccPasswdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAccPasswdWidget)
{
    ui->setupUi(this);

    //ui->btnAdd->setEnabled();



    //直接操作数据库
//    ui->tableViewPrivate->setShowGrid(false); //设置不显示格子线
    ui->tableViewPrivate->horizontalHeader()->setStyleSheet( \
                "QHeaderView::section{font:14px 'Microsoft YaHei UI';" \
                                      "border-bottom:3px solid #DEE1E4;}"); //设置表头背景色
    ui->tableViewPrivate->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewPrivate->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);
    ui->tableViewPrivate->verticalHeader()->hide();
    ui->tableViewPrivate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    // 让列头可被点击，触发点击事件
    //ui->tableViewPrivate->horizontalHeader()->setSectionsClickable(true);
    // 去掉选中表格时，列头的文字高亮
    //ui->tableViewPrivate->horizontalHeader()->setHighlightSections(false);
    //ui->tableViewPrivate->horizontalHeader()->setBackgroundRole(QPalette::Background);
    // 列头灰色
   // ui->tableViewPrivate->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");
    //connect(ui->tableViewPrivate->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    QSqlTableModel* pApasswdTableModel = new QSqlTableModel(this);
    pApasswdTableModel->setTable("tAPasswd");
    // 三种提交方式，改动即提交，选择其他行时提交，手动提交；经实际测试，其中只有手动提交在显示效果上是最好的
        pApasswdTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //pApasswdTableModel->setFilter();
//    pApasswdTableModel->setQuery("select item account passwd form tAPasswd where uid ="
//                                 + QString::number(CUser::getInstance()->getUid()));
    pApasswdTableModel->select();
    pApasswdTableModel->removeColumn(0); // 不显示aid列
    pApasswdTableModel->setHeaderData(0, Qt::Horizontal, "当前账户");
    pApasswdTableModel->setHeaderData(1, Qt::Horizontal, "栏目");
    pApasswdTableModel->setHeaderData(2, Qt::Horizontal, "账号");
    pApasswdTableModel->setHeaderData(3, Qt::Horizontal, "密码");
    ui->tableViewPrivate->setModel(pApasswdTableModel);
}

CAccPasswdWidget::~CAccPasswdWidget()
{
    delete ui;
}

void CAccPasswdWidget::on_btnAdd_clicked()
{
    QSqlTableModel* model = (QSqlTableModel*)ui->tableViewPrivate->model();
    int rowNum = model->rowCount(); //获得表的行数
        model->insertRow(rowNum); //添加一行
        //model->setData(model->index(rowNum, 0), CDairyApp::userInfo().uid);
        //model->submitAll(); //可以直接提交
}

void CAccPasswdWidget::on_btnCommit_clicked()
{
    QSqlTableModel *pModel = dynamic_cast<QSqlTableModel *>(ui->tableViewPrivate->model());
        pModel->database().transaction(); //开始事务操作
        if (pModel->submitAll()) // 提交所有被修改的数据到数据库中
        {
            pModel->database().commit(); //提交成功，事务将真正修改数据库数据
        }
        else
        {
            pModel->database().rollback(); //提交失败，事务回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pModel->lastError().text()));
        }
        //pModel->revertAll(); //撤销修改
}

void CAccPasswdWidget::on_btnDelete_clicked()
{
    QSqlTableModel* model = (QSqlTableModel*)ui->tableViewPrivate->model();
    int curRow = ui->tableViewPrivate->currentIndex().row();
        //获取选中的行
        model->removeRow(curRow);
        //删除该行
        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        {
           model->revertAll(); //如果不删除，则撤销
        }
        else
        {
            model->submitAll(); //否则提交，在数据库中删除该行
        }
}

