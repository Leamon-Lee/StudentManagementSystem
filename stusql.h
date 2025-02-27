#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include <QSqlDatabase>

struct StuInfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;
    quint32 phone;
    QString wechat;
};

struct UserInfo{
    QString username;
    QString password;
    QString auth;
};

class stuSql : public QObject
{
    Q_OBJECT
public:
    explicit stuSql(QObject *parent = nullptr);

    static stuSql *ptrstuSql;
    static stuSql *getInstance() {
        if(nullptr == ptrstuSql){
            ptrstuSql = new stuSql;
        }
        return ptrstuSql;
    }

    // 打开数据库
    void init();

    // 查询所有学生数量
    quint32 getStuCnt();

    // 查询第几页学生数据
    QList<StuInfo>  getPageStu(quint32 page, quint32 uiCnt);

    // 增加学生
    bool addStu(StuInfo);

    // 删除学生
    bool delStu(int id);

    // 是否存在id
    bool isIdExist(int id);

    // 清空学生表
    bool clearStuTable();

    // 修改学生信息
    bool updateStuInfo(StuInfo info);

    // 查询学生ID的序号
    int searchId(int id);

    // 查询所有用户
    QList<UserInfo> getAllUser();

    // 查询用户名是否存在
    bool isExit(QString strUser);

    // 修改用户信息
    bool updateUserInfo(UserInfo info);

    // 添加单个用户
    bool addUser(UserInfo info);

    // 删除单个用户
    bool delUser(QString strUserName);

signals:

private:
    QSqlDatabase db;

};

#endif // STUSQL_H
