#ifndef DLG_STU_H
#define DLG_STU_H

#include <QDialog>

namespace Ui {
class Dlg_stu;
}

class Dlg_stu : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_stu(QWidget *parent = nullptr);
    ~Dlg_stu();

private:
    Ui::Dlg_stu *ui;
};

#endif // DLG_STU_H
