#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrStuSql(nullptr)
{
    ui->setupUi(this);

    m_dlgLogin.show();
    auto f = [&](){
        this->show();
    };

    connect(&m_dlgLogin, &Page_login::sendLoginSuccess, this, f);

    // 左侧 treeWidget 初始化
    ui -> treeWidget -> clear();
    ui -> treeWidget -> setColumnCount(1);
    QTreeWidgetItem *fp = new QTreeWidgetItem(ui->treeWidget, QStringList("学生管理系统"));
    ui -> treeWidget -> addTopLevelItem(fp);
    ui -> treeWidget -> addTopLevelItem(new QTreeWidgetItem(fp, QStringList("学生管理")));
    ui -> treeWidget -> addTopLevelItem(new QTreeWidgetItem(fp, QStringList("管理员管理")));

    m_ptrStuSql = stuSql::getInstance();

    m_lNames = {
        "赵思远", "钱梦瑶", "孙宇航", "李子萱", "周俊杰", "吴紫妍", "郑泽洋", "王雨桐", "冯思琪", "陈浩宇",
        "褚伟", "卫芳", "蒋强", "沈敏", "韩丽", "杨勇", "朱静", "秦磊", "尤娜", "何杰",
        "吕思远", "施梦瑶", "张宇航", "孔子萱", "曹俊杰", "严紫妍", "华泽洋", "金雨桐", "魏思琪", "陶浩宇",
        "姜伟", "赵芳", "钱强", "孙敏", "李丽", "周勇", "吴静", "郑磊", "王娜", "冯杰",
        "陈思远", "褚梦瑶", "卫宇航", "蒋子萱", "沈俊杰", "韩紫妍", "杨泽洋", "朱雨桐", "秦思琪", "尤浩宇",
        "何伟", "吕芳", "施强", "张敏", "孔丽", "曹勇", "严静", "华磊", "金娜", "魏杰",
        "陶思远", "姜梦瑶", "赵宇航", "钱子萱", "孙俊杰", "卫紫妍", "李泽洋", "周雨桐", "冯思琪", "陈浩宇",
        "褚伟", "卫芳", "蒋强", "沈敏", "韩丽", "杨勇", "朱静", "秦磊", "尤娜", "何杰",
        "吕思远", "施梦瑶", "张宇航", "孔子萱", "曹俊杰", "严紫妍", "华泽洋", "金雨桐", "魏思琪", "陶浩宇",
        "姜伟", "赵芳", "钱强", "孙敏", "李丽", "周勇", "吴静", "郑磊", "王娜", "冯杰",
        "陈思远", "褚梦瑶", "卫宇航", "蒋子萱", "沈俊杰", "韩紫妍", "杨泽洋", "朱雨桐", "秦思琪", "尤浩宇",
        "何伟", "吕芳", "施强", "张敏", "孔丽", "曹勇", "严静", "华磊", "金娜", "魏杰"
    };

    stuRefresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}


void MainWindow::on_btn_simul_clicked()
{
    StuInfo info;
    QRandomGenerator g;
    g.seed(0);
    for(int i = 0; i < m_lNames.size(); i ++){
        info.id      = i+1;
        info.name    = m_lNames[i];
        info.age     = g.bounded(10, 18);
        info.grade   = g.bounded(7, 10);
        info.uiclass = g.bounded(1, 10);
        info.phone   = g.bounded(1000000, 9999999);
        info.wechat  = "wechat";

        m_ptrStuSql -> addStu(info);
    }
    stuRefresh();

}


void MainWindow::on_btn_refresh_clicked()
{
    stuRefresh();
}


// 学生表格页面刷新
void MainWindow::stuRefresh()
{
    auto cnt = m_ptrStuSql -> getStuCnt();
    QList<StuInfo> lStudents = m_ptrStuSql -> getPageStu(0, cnt);
    ui -> tableWidget -> clearContents();
    ui -> tableWidget -> setRowCount(cnt);
    for(int i = 0; i < lStudents.size(); i ++){
        ui -> tableWidget -> setItem(i, 0, new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui -> tableWidget -> setItem(i, 1, new QTableWidgetItem(lStudents[i].name));
        ui -> tableWidget -> setItem(i, 2, new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui -> tableWidget -> setItem(i, 3, new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui -> tableWidget -> setItem(i, 4, new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui -> tableWidget -> setItem(i, 5, new QTableWidgetItem(QString::number(lStudents[i].phone)));
        ui -> tableWidget -> setItem(i, 6, new QTableWidgetItem(lStudents[i].wechat));
    }
}

void MainWindow::userRefresh()
{

}


void MainWindow::on_btn_add_clicked()
{
    StuInfo info;
    info.id      = -1;
    info.name    = NULL;
    info.age     = -1;
    info.grade   = -1;
    info.uiclass = -1;
    info.phone   = -1;
    info.wechat  = NULL;
    m_dlg_add_stu.setType(false, info);
    m_dlg_add_stu.exec();
    stuRefresh();
}


void MainWindow::on_btn_revise_clicked()
{
    StuInfo info;
    int i = ui->tableWidget->currentRow();
    if(i >= 0){
        info.id      = ui -> tableWidget -> item(i, 0) -> text().toUInt();
        info.name    = ui -> tableWidget -> item(i, 1) -> text();
        info.age     = ui -> tableWidget -> item(i, 2) -> text().toUInt();
        info.grade   = ui -> tableWidget -> item(i, 3) -> text().toUInt();
        info.uiclass = ui -> tableWidget -> item(i, 4) -> text().toUInt();
        info.phone   = ui -> tableWidget -> item(i, 5) -> text().toUInt();
        info.wechat  = ui -> tableWidget -> item(i, 6) -> text();
    }
    m_dlg_add_stu.setType(true, info);
    m_dlg_add_stu.exec();
    stuRefresh();
}


void MainWindow::on_btn_delete_clicked()
{
    int i = ui -> tableWidget -> currentRow();
    if(i >= 0){
        int id = ui -> tableWidget -> item(i, 0) -> text().toUInt();
        m_ptrStuSql -> delStu(id);
        stuRefresh();
    }
}


void MainWindow::on_btn_search_clicked()
{
    auto ptr = stuSql::getInstance();
    int id = ui -> search_id -> text().toUInt();
    if(!ptr->isIdExist(id)){
        QMessageBox::warning(this, "ID 不存在", "该 ID 不存在，请输入其他 ID。");
    }else{
        int i = ptr->searchId(id)+1;
        StuInfo info;
        if(i >= 0){
            info.id      = ui -> tableWidget -> item(i, 0) -> text().toUInt();
            info.name    = ui -> tableWidget -> item(i, 1) -> text();
            info.age     = ui -> tableWidget -> item(i, 2) -> text().toUInt();
            info.grade   = ui -> tableWidget -> item(i, 3) -> text().toUInt();
            info.uiclass = ui -> tableWidget -> item(i, 4) -> text().toUInt();
            info.phone   = ui -> tableWidget -> item(i, 5) -> text().toUInt();
            info.wechat  = ui -> tableWidget -> item(i, 6) -> text();
        }
        m_dlg_add_stu.setType(true, info);
        m_dlg_add_stu.exec();
    }
    stuRefresh();
}

