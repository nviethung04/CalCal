#include <QApplication>
#include "include/mainwindow.h"
#include "include/inputdialog.h"
#include "include/databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Khai báo và cấu hình cơ sở dữ liệu
    QSqlDatabase& mydb = DatabaseManager::getDatabase();

    if (!mydb.open()) {
        // Xử lý lỗi kết nối cơ sở dữ liệu
        qDebug() << "Khong the ket noi CSDL:" << mydb.lastError();
        return -1;
    }
/*
    // Kiểm tra bảng NGUOIDUNG
    QSqlQuery query(mydb);
    query.exec("SELECT COUNT(*) FROM NGUOIDUNG");
    query.next();
    int count = query.value(0).toInt();
    if (count == 0) {
        InputDialog inputDialog;

        // Tạo con trỏ MainWindow
        MainWindow* mainWindow = new MainWindow;

        // Kết nối tín hiệu saveButtonClicked của inputDialog tới một khe cắm (slot)
        QObject::connect(&inputDialog, &InputDialog::saveButtonClicked, [&]() {

            // Đóng inputDialog
            inputDialog.close();

            // Hiển thị MainWindow
            mainWindow->show();
        });

        inputDialog.exec(); // Hiển thị inputdialog
    } else {
        // Bảng NGUOIDUNG có dữ liệu, mở MainWindow
*/
        MainWindow mainWindow;
        mainWindow.show();

    // Chạy vòng lặp sự kiện chính
    return app.exec();
}
