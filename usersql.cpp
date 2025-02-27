#include "usersql.h"
#include "qsqlquery.h"



usersql::usersql(QObject *parent)
    : QObject{parent}
{}

bool usersql::isUserExist(QString username)
{
    QSqlQuery sql(db);
    sql.exec(QString("select * from username where username = '%1'").arg(username));
    return sql.next();
}

bool usersql::verifyPassword(QString password)
{
    QSqlQuery sql(db);
    sql.exec(QString("select * from username where password = '%1'").arg(password));
    return sql.next();
}
