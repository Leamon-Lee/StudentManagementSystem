#include "dlg_stu.h"
#include "ui_dlg_stu.h"

Dlg_stu::Dlg_stu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_stu)
{
    ui->setupUi(this);
}

Dlg_stu::~Dlg_stu()
{
    delete ui;
}
