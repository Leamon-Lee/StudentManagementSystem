#include "mainwindow.h"
#include "page_login.h"
#include "stusql.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    stuSql sql;
    return a.exec();
}
