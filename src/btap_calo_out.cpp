#include "include/btap_calo_out.h"
#include "ui_btap_calo_out.h"
#include "include/databasemanager.h"
#include <QInputDialog>

btap_calo_out::btap_calo_out(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::btap_calo_out)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &btap_calo_out::on_pushButton_clicked);
}

btap_calo_out::~btap_calo_out()
{
    clearTable();
    delete ui;
}

void btap_calo_out::on_pushButton_clicked()
{
    // Đóng cửa sổ
    close();
    // Gửi tín hiệu closed()
    emit closed();
}

void btap_calo_out::loadCaloFromDatabase()
{
    clearTable();
    // Truy vấn cơ sở dữ liệu để lấy dữ liệu thực phẩm
    QSqlQuery query(mydb);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString queryString = QString("SELECT Ngay, MaBT, Thoi_gian, Calo_tieu_thu FROM CALO_OUT WHERE Ngay='%1'").arg(currentDate);
    if (query.exec(queryString)) {
        int row = 0;
        while (query.next()) {
            QString today= query.value(0).toString();
            int btapId = query.value(1).toInt();
            int time = query.value(2).toInt();
            float calories = query.value(3).toFloat();

            // Hiển thị thông tin trong bảng
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(today));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(btapId)));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(time)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(calories)));
        }
    }
}

void btap_calo_out::clearTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
