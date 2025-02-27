#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dlg_add_stu.h>
#include "page_login.h"
#include "stusql.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_exit_clicked();

    void on_btn_simul_clicked();

    void on_btn_refresh_clicked();

    void on_btn_add_clicked();

    void on_btn_revise_clicked();

    void on_btn_delete_clicked();

    void on_btn_search_clicked();

private:
    Ui::MainWindow *ui;
    Page_login m_dlgLogin;
    stuSql *m_ptrStuSql;
    QStringList m_lNames;

    dlg_add_stu m_dlg_add_stu;

    void stuRefresh();
    void userRefresh();
};
#endif // MAINWINDOW_H
