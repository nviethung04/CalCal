#include "include/food_calo_in.h"
#include "ui_food_calo_in.h"
#include "include/databasemanager.h"
#include <QInputDialog>

food_calo_in::food_calo_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::food_calo_in)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &food_calo_in::on_pushButton_clicked);
}

food_calo_in::~food_calo_in()
{
    clearTable();
    delete ui;
}

void food_calo_in::on_pushButton_clicked()
{
    // Đóng cửa sổ
    close();
    // Gửi tín hiệu closed()
    emit closed();
}

void food_calo_in::loadCaloFromDatabase()
{
    clearTable();
    // Truy vấn cơ sở dữ liệu để lấy dữ liệu thực phẩm
    QSqlQuery query(mydb);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString queryString = QString("SELECT Ngay, MaTP, So_luong, Calo_thuc_nap FROM CALO_IN WHERE Ngay='%1'").arg(currentDate);
    if (query.exec(queryString)) {
        int row = 0;
        while (query.next()) {
            QString today= query.value(0).toString();
            int foodId = query.value(1).toInt();
            double quantity = query.value(2).toDouble();
            float calories = query.value(3).toFloat();

            // Hiển thị thông tin trong bảng
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(today));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(foodId)));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(calories)));
        }
    }
}

void food_calo_in::clearTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
