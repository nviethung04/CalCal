#include "include/btaptab.h"
#include "ui_btaptab.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "include/btap_calo_out.h"
#include "include/databasemanager.h"
#include <QInputDialog>

btapTab::btapTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::btapTab)
{
    ui->setupUi(this);

    connect(&m_btap_calo_out, &btap_calo_out::closed, this, &btapTab::updateTotalCalories);

    connect(ui->detailButton, &QPushButton::clicked, this, &btapTab::on_detailButton_clicked);

    loadFromDatabase();
}

btapTab::~btapTab()
{
    delete ui;
}

//Cập nhật Tổng lượng calo đã nạp
void btapTab::updateTotalCalories()
{
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    // Truy vấn cơ sở dữ liệu để tính tổng lượng calo đã nạp trong ngày
    QSqlQuery query(mydb);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString queryString = QString("SELECT SUM(Calo_tieu_thu) FROM CALO_OUT WHERE Ngay='%1'").arg(currentDate);
    if (query.exec(queryString) && query.next()) {
        double totalCalories = query.value(0).toDouble();
        // Cập nhật giá trị tổng lượng calo đã nạp trong ngày vào caloLabel
        ui->calolabel->setText("CALO TIÊU THỤ: " + QString::number(totalCalories));
    }
}

//Sự kiện khi nhấn nút "Chi tiết"
void btapTab::on_detailButton_clicked()
{
    ////
    m_btap_calo_out.clearTable();
    m_btap_calo_out.loadCaloFromDatabase();
    // Hiển thị giao diện food_calo_in
    m_btap_calo_out.setModal(true);
    m_btap_calo_out.show(); // Sử dụng show() để hiển thị cửa sổ

}

//Sự kiện khi ấn nút thêm
void btapTab::buttonAdd_clicked()
{
 // Hiển thị hộp thoại để nhập số lượng
    bool ok;
    int time = QInputDialog::getInt(this, tr("Nhập thời gian"), tr("Thời gian (phút):"), 1, 1, 2000, 1, &ok);

    if (ok) {
        // Lấy thông tin từ dòng tương ứng
        int row = ui->tableWidget->currentRow();
        int btapId = ui->tableWidget->item(row, 0)->text().toInt();
        float caloriesPer60 = ui->tableWidget->item(row, 2)->text().toFloat();

        // Tính toán số calo thực tế
        float caloriesout = (time / 60.0) * caloriesPer60;

        // Thêm dữ liệu vào bảng CALO_IN
        QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
        QString queryString = "INSERT INTO CALO_OUT (Ngay, MaBT, Thoi_gian, Calo_tieu_thu) VALUES (:date, :btapId, :time, :calories)";
        QSqlQuery query(mydb);
        query.prepare(queryString);
        query.bindValue(":date", currentDate);
        query.bindValue(":btapId", btapId);
        query.bindValue(":time", time);
        query.bindValue(":calories", caloriesout);


        if (query.exec()) {
            // Hiển thị thông báo thành công
            QMessageBox::information(this, tr("Thành công"), tr("Bài tập đã được thêm vào danh sách."));
        } else {
            // Xử lý lỗi khi thêm dữ liệu vào bảng CALO_IN
            QMessageBox::warning(this, tr("Lỗi"), tr("Không thể thêm dữ liệu."));
            qDebug() << "Khong the chay truy van." << query.lastError();
        }

        //Gọi hàm để update lượng Calo tổng đã tiêu thụ
        updateTotalCalories();
    }
}

//Tải DS bài tập từ CSDL truyền vào bảng
void btapTab::loadFromDatabase()
{
    // Truy vấn cơ sở dữ liệu để lấy dữ liệu thực phẩm
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    QString queryString = "SELECT MaBT, TenBT, Luong_Calo_moi_60p FROM BAITAP";
    if (query.exec(queryString)) {
        int row = 0;
        while (query.next()) {
            int btapId = query.value(0).toInt();
            QString btapName = query.value(1).toString();
            float calories = query.value(2).toFloat();

            // Hiển thị thông tin trong bảng
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(btapId)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(btapName));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(calories)));

            // Tạo nút "Thêm" và đặt vào cột bổ sung
            QPushButton* addButton = new QPushButton("Thêm");
                connect(addButton, &QPushButton::clicked, this, &btapTab::buttonAdd_clicked);
            ui->tableWidget->setCellWidget(row, 3, addButton);

            row++;
        }
    } else {
            qDebug() << "Khong the chay truy van." << query.lastError();
            return;
        }
}
