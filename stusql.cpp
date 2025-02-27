#include "stusql.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <qapplication.h>

stuSql *stuSql::ptrstuSql = nullptr;

stuSql::stuSql(QObject *parent)
    : QObject{parent}
{
    init();
}

// 打开数据库
void stuSql::init(){
    stuSql::db = QSqlDatabase::addDatabase("QSQLITE");
    if(QSqlDatabase::drivers().isEmpty()){
        qDebug() << "No found database drivers.";
        return;
    }
#if 0
    auto str = QApplication::applicationDirPath()+"data.db";
    qDebug() << str;
#endif
    db.setDatabaseName("D:\\Desktop\\data.db");
    if(!db.open()){
        qDebug() << "database cannot open.";
    }
}

// 查询所有学生数量
quint32 stuSql::getStuCnt() {
    quint32 uiCnt = 0;
    QSqlQuery sql(db);
    sql.exec("select count(id) from student;");
    while(sql.next()){
        uiCnt = sql.value(0).toUInt();
    }

    return uiCnt;
}

// 查询第几页学生数据
QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 uiCnt) {
    QList<StuInfo> l;
    QSqlQuery sql(db);
    QString strsql = QString("select * from student order by id limit %1 offset %2")
                         .arg(uiCnt)
                         .arg(page*uiCnt);
    sql.exec(strsql);

    StuInfo info;
    while(sql.next()){
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.age = sql.value(2).toUInt();
        info.grade = sql.value(3).toUInt();
        info.uiclass = sql.value(4).toUInt();
        info.phone = sql.value(5).toUInt();
        info.wechat = sql.value(6).toString();
        l.push_back(info);
    }
    return l;
}

// 增加学生
bool stuSql::addStu(StuInfo info) {
    QSqlQuery sql(db);
    QString strSql = QString("insert into student values(%1, '%2', %3, %4, %5, '%6', '%7')")
                         .arg(info.id)
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.phone)
                         .arg(info.wechat);
    return sql.exec(strSql);
}

// 删除学生
bool stuSql::delStu(int id) {
    QSqlQuery sql(db);
    return sql.exec(QString("delete from student where id = %1").arg(id));
}

// 是否存在id
bool stuSql::isIdExist(int id) {
    QSqlQuery query(db);
    query.prepare("SELECT id FROM student WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError();
        return false;
    }

    return query.next(); // True if a record was found
}

// 清空学生表
bool stuSql::clearStuTable() {
    QSqlQuery sql(db);
    return sql.exec("delete from student");
}

// 修改学生信息
bool stuSql::updateStuInfo(StuInfo info) {
    QSqlQuery sql(db);
    QString strSql = QString("update student set name = '%1', age = %2, "
                             "grade = %3, uiclass = %4, phone = %5, wechat = '%6', id = '%7'")
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.phone)
                         .arg(info.wechat)
                         .arg(info.id);
    return sql.exec(strSql);
}

// 查询学生ID的序号
int stuSql::searchId(int id) {
    QSqlQuery query(db);
    query.prepare("SELECT id FROM student WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "查询失败:" << query.lastError().text();
        return -1;
    }

    return query.next() ? query.value(0).toInt() : -1;
}

// 查询所有用户
QList<UserInfo> stuSql::getAllUser() {
    QList<UserInfo> l;
    QSqlQuery sql(db);
    QString strsql = QString("select * from username");
    sql.exec(strsql);

    UserInfo info;
    while(sql.next()){
        info.username = sql.value(0).toString();
        info.password = sql.value(1).toString();
        info.auth = sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

// 查询用户名是否存在
bool stuSql::isExit(QString strUser) {
    QSqlQuery sql(db);
    sql.exec(QString("select * from username where username = '%1'").arg(strUser));
    return sql.next();
}

// 修改用户信息
bool stuSql::updateUserInfo(UserInfo info) {
    QSqlQuery sql(db);
    QString strSql = QString("update username set username = '%1', password = '%2', auth = '%3'")
                         .arg(info.username, info.password, info.auth);
    return sql.exec(strSql);
}

// 添加单个用户
bool stuSql::addUser(UserInfo info) {
    QSqlQuery sql(db);
    QString strSql = QString("insert into username values('%1', '%2', '%3')")
                         .arg(info.username, info.password, info.auth);
    return sql.exec(strSql);
}

// 删除单个用户
bool stuSql::delUser(QString strUserName) {
    QSqlQuery sql(db);
    return sql.exec(QString("delete from username where username = %1").arg(strUserName));
}
