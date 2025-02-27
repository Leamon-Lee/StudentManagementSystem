#include "dlg_delete_stu.h"
#include "ui_dlg_delete_stu.h"

dlg_delete_stu::dlg_delete_stu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dlg_delete_stu)
{
    ui->setupUi(this);
}

dlg_delete_stu::~dlg_delete_stu()
{
    delete ui;
}
