#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

class DatabaseManager
{
public:
    static QSqlDatabase& getDatabase();

private:
    static QSqlDatabase mydb;
};

#endif // DATABASEMANAGER_H
