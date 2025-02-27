#ifndef DLG_ADD_STU_H
#define DLG_ADD_STU_H

#include "stusql.h"

#include <QDialog>

namespace Ui {
class dlg_add_stu;
}

class dlg_add_stu : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_add_stu(QWidget *parent = nullptr);
    ~dlg_add_stu();

    void setType(bool flag, StuInfo info);

private slots:
    void on_btn_add_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::dlg_add_stu *ui;

};

#endif // DLG_ADD_STU_H
