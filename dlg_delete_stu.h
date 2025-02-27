#ifndef DLG_DELETE_STU_H
#define DLG_DELETE_STU_H

#include <QDialog>

namespace Ui {
class dlg_delete_stu;
}

class dlg_delete_stu : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_delete_stu(QWidget *parent = nullptr);
    ~dlg_delete_stu();

private:
    Ui::dlg_delete_stu *ui;
};

#endif // DLG_DELETE_STU_H
