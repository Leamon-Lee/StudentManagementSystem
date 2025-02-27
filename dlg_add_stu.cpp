#include "dlg_add_stu.h"
#include "ui_dlg_add_stu.h"
#include "stusql.h"

#include <Qstring>
#include <QMessageBox> // 确保包含消息框头文件

dlg_add_stu::dlg_add_stu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dlg_add_stu)
{
    ui->setupUi(this);
}

dlg_add_stu::~dlg_add_stu()
{
    delete ui;
}

void dlg_add_stu::on_btn_add_clicked()
{
    auto ptr = stuSql::getInstance();
    StuInfo info;

    // 数据转换部分保持不变
    info.id = ui->le_id->text().toInt();
    info.name = ui->le_name->text();
    info.age = static_cast<quint8>(ui->le_age->text().toUInt());
    info.grade = static_cast<quint16>(ui->le_grade->text().toUInt());
    info.uiclass = static_cast<quint16>(ui->le_uiclass->text().toUInt());
    info.phone = ui->le_phone->text().toUInt();
    info.wechat = ui->le_wechat->text();

    if (ptr->addStu(info)) {
        this->close();
    }
}


void dlg_add_stu::on_btn_cancel_clicked()
{
    this -> close();
}

void dlg_add_stu::setType(bool flag, StuInfo info)
{
    if(flag){
        ui -> le_id      -> setText(QString::number(info.id));
        ui -> le_name    -> setText(info.name);
        ui -> le_age     -> setText(QString::number(info.age));
        ui -> le_grade   -> setText(QString::number(info.grade));
        ui -> le_uiclass -> setText(QString::number(info.uiclass));
        ui -> le_phone   -> setText(QString::number(info.phone));
        ui -> le_wechat  -> setText(info.wechat);
    }else{
        ui -> le_id      -> clear();
        ui -> le_name    -> clear();
        ui -> le_age     -> clear();
        ui -> le_grade   -> clear();
        ui -> le_uiclass -> clear();
        ui -> le_phone   -> clear();
        ui->le_wechat    -> clear();
    }

}

