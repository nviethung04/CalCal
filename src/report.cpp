#include "include/report.h"
#include "ui_report.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "include/databasemanager.h"
#include <QInputDialog>

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    QString arg1 = ui->comboBox->currentText();
    if (arg1 == "Theo ngày"){
        // Lấy thông tin calo in trong ngày từ bảng CALO_IN
        QString queryString = "SELECT Ngay, SUM(Calo_thuc_nap) AS TongCaloIn FROM CALO_IN GROUP BY Ngay";
    query.exec(queryString);

    int row = 0;

    // Lặp qua kết quả truy vấn calo in
    while (query.next()) {
        QString ngay = query.value("Ngay").toString();
        double tongCaloIn = query.value("TongCaloIn").toDouble();

        // Lấy thông tin calo out trong ngày từ bảng CALO_OUT
        queryString = "SELECT SUM(Calo_tieu_thu) AS TongCaloOut FROM CALO_OUT WHERE Ngay = :ngay";
        query.prepare(queryString);
        query.bindValue(":ngay", ngay);
        query.exec();

        if (query.next()) {
            double tongCaloOut = query.value("TongCaloOut").toDouble();
            double chenhLechCalo = tongCaloIn - tongCaloOut;

            // Chèn dữ liệu vào Table Widget
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ngay));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(tongCaloIn)));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(tongCaloOut)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(chenhLechCalo)));

            row++;
        }
    }

    // Hiển thị Table Widget
    ui->tableWidget->resizeColumnsToContents();
}
else {
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);

    // Lấy ngày đầu tháng và ngày hiện tại
    QDate currentDate = QDate::currentDate();
    QDate firstDayOfMonth(currentDate.year(), currentDate.month(), 1);
    int numberOfDays = firstDayOfMonth.daysInMonth();

    int row = 0;

    // Lặp qua từng ngày trong tháng hiện tại
    for (int day = 1; day <= numberOfDays; day++) {
        QDate currentDate(firstDayOfMonth.year(), firstDayOfMonth.month(), day);
        QString dateString = currentDate.toString("yyyy-MM-dd");

        // Lấy thông tin calo in cho ngày hiện tại từ bảng CALO_IN
        QString queryString = "SELECT SUM(Calo_thuc_nap) AS TongCaloIn FROM CALO_IN WHERE Ngay = :ngay";
        query.prepare(queryString);
        query.bindValue(":ngay", dateString);
        query.exec();

        double tongCaloIn = 0.0;
        if (query.next() && query.value("TongCaloIn").isValid()) {
            tongCaloIn = query.value("TongCaloIn").toDouble();
        }

        // Lấy thông tin calo out cho ngày hiện tại từ bảng CALO_OUT
        queryString = "SELECT SUM(Calo_tieu_thu) AS TongCaloOut FROM CALO_OUT WHERE Ngay = :ngay";
        query.prepare(queryString);
        query.bindValue(":ngay", dateString);
        query.exec();

        double tongCaloOut = 0.0;
        if (query.next() && query.value("TongCaloOut").isValid()) {
            tongCaloOut = query.value("TongCaloOut").toDouble();
        }

        double chenhLechCalo = tongCaloIn - tongCaloOut;

        // Chèn dữ liệu vào Table Widget
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(dateString));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(tongCaloIn)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(tongCaloOut)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(chenhLechCalo)));

        row++;
    }

    // Hiển thị Table Widget
    ui->tableWidget->resizeColumnsToContents();

}
}
Report::~Report()
{
    delete ui;
}


void Report::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    if (arg1 == "Theo ngày"){
    // Lấy thông tin calo in trong ngày từ bảng CALO_IN
    QString queryString = "SELECT Ngay, SUM(Calo_thuc_nap) AS TongCaloIn FROM CALO_IN GROUP BY Ngay";
    query.exec(queryString);

    int row = 0;

    // Lặp qua kết quả truy vấn calo in
    while (query.next()) {
    QString ngay = query.value("Ngay").toString();
    double tongCaloIn = query.value("TongCaloIn").toDouble();

    // Lấy thông tin calo out trong ngày từ bảng CALO_OUT
    queryString = "SELECT SUM(Calo_tieu_thu) AS TongCaloOut FROM CALO_OUT WHERE Ngay = :ngay";
    query.prepare(queryString);
    query.bindValue(":ngay", ngay);
    query.exec();

    if (query.next()) {
        double tongCaloOut = query.value("TongCaloOut").toDouble();
        double chenhLechCalo = tongCaloIn - tongCaloOut;

        // Chèn dữ liệu vào Table Widget
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ngay));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(tongCaloIn)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(tongCaloOut)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(chenhLechCalo)));

        row++;
    }
    }

    // Hiển thị Table Widget
    ui->tableWidget->resizeColumnsToContents();
}
else {
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);

    // Lấy ngày đầu tháng và ngày hiện tại
    QDate currentDate = QDate::currentDate();
    QDate firstDayOfMonth(currentDate.year(), currentDate.month(), 1);
    int numberOfDays = firstDayOfMonth.daysInMonth();

    int row = 0;

    // Lặp qua từng ngày trong tháng hiện tại
    for (int day = 1; day <= numberOfDays; day++) {
    QDate currentDate(firstDayOfMonth.year(), firstDayOfMonth.month(), day);
    QString dateString = currentDate.toString("yyyy-MM-dd");

    // Lấy thông tin calo in cho ngày hiện tại từ bảng CALO_IN
    QString queryString = "SELECT SUM(Calo_thuc_nap) AS TongCaloIn FROM CALO_IN WHERE Ngay = :ngay";
    query.prepare(queryString);
    query.bindValue(":ngay", dateString);
    query.exec();

    double tongCaloIn = 0.0;
    if (query.next() && query.value("TongCaloIn").isValid()) {
        tongCaloIn = query.value("TongCaloIn").toDouble();
    }

    // Lấy thông tin calo out cho ngày hiện tại từ bảng CALO_OUT
    queryString = "SELECT SUM(Calo_tieu_thu) AS TongCaloOut FROM CALO_OUT WHERE Ngay = :ngay";
    query.prepare(queryString);
    query.bindValue(":ngay", dateString);
    query.exec();

    double tongCaloOut = 0.0;
    if (query.next() && query.value("TongCaloOut").isValid()) {
        tongCaloOut = query.value("TongCaloOut").toDouble();
    }

    double chenhLechCalo = tongCaloIn - tongCaloOut;

    // Chèn dữ liệu vào Table Widget
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(dateString));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(tongCaloIn)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(tongCaloOut)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(chenhLechCalo)));

    row++;
    }

    // Hiển thị Table Widget
    ui->tableWidget->resizeColumnsToContents();

}
}


