#include "include/databasemanager.h"

QSqlDatabase DatabaseManager::mydb;

QSqlDatabase& DatabaseManager::getDatabase()
{
    if (!mydb.isValid()) {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("F:/Projects/cse481/64KTPM2_8_CalCal/CalCal/data/CalCaldb.db");

        if (!mydb.open()) {
            qDebug() << "Không thể mở kết nối cơ sở dữ liệu:" << mydb.lastError();
        }
    }

    return mydb;
}
