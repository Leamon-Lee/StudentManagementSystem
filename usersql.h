#ifndef USERSQL_H
#define USERSQL_H

#include <QObject>
#include <QSqlDatabase>

class usersql : public QObject
{
    Q_OBJECT
public:
    explicit usersql(QObject *parent = nullptr);

    // 检查是否存在user
    bool isUserExist(QString username);

    // 检查user密码是否合正确
    bool verifyPassword(QString password);


signals:

public:
    QSqlDatabase db;
};

#endif // USERSQL_H
