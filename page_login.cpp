#include "page_login.h"
#include "ui_page_login.h"
#include "usersql.h"

Page_login::Page_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page_login)
{
    ui->setupUi(this);
}

Page_login::~Page_login()
{
    delete ui;
}

void Page_login::on_btn_login_clicked()
{
    // 数据库查找用户名和密码

    // 失败就提示

    // 成功就进入主页

    emit sendLoginSuccess();

}


void Page_login::on_btn_exist_clicked()
{
    // 退出
    exit(0);
}

