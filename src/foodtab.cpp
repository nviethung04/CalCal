#include "include/foodtab.h"
#include "ui_foodtab.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "include/food_calo_in.h"
#include "include/databasemanager.h"
#include <QInputDialog>

FoodTab::FoodTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FoodTab)
{
    ui->setupUi(this);

    connect(&m_food_calo_in, &food_calo_in::closed, this, &FoodTab::updateTotalCalories);

    connect(ui->detailButton, &QPushButton::clicked, this, &FoodTab::on_detailButton_clicked);

    loadFoodsFromDatabase();
}

FoodTab::~FoodTab()
{
    delete ui;
}

//Cập nhật Tổng lượng calo đã nạp
void FoodTab::updateTotalCalories()
{
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    // Truy vấn cơ sở dữ liệu để tính tổng lượng calo đã nạp trong ngày
    QSqlQuery query(mydb);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString queryString = QString("SELECT SUM(Calo_thuc_nap) FROM CALO_IN WHERE Ngay='%1'").arg(currentDate);
    if (query.exec(queryString) && query.next()) {
        double totalCalories = query.value(0).toDouble();
        // Cập nhật giá trị tổng lượng calo đã nạp trong ngày vào caloLabel
        ui->calolabel->setText("CALO ĐÃ NẠP: " + QString::number(totalCalories));
    }
}

//Sự kiện khi nhấn nút "Chi tiết"
void FoodTab::on_detailButton_clicked()
{
    m_food_calo_in.clearTable();
    ////
    m_food_calo_in.loadCaloFromDatabase();
    // Hiển thị giao diện food_calo_in
    m_food_calo_in.setModal(true);
    m_food_calo_in.show(); // Sử dụng show() để hiển thị cửa sổ

}

//Sự kiện khi ấn nút thêm
void FoodTab::buttonAdd_clicked()
{
 // Hiển thị hộp thoại để nhập số lượng
    bool ok;
    double quantity = QInputDialog::getDouble(this, tr("Nhập số lượng"), tr("Số lượng:"), 1, 1, 10000, 1, &ok);

    if (ok) {
        // Lấy thông tin từ dòng tương ứng
        int row = ui->tableWidget->currentRow();
        int foodId = ui->tableWidget->item(row, 0)->text().toInt();
        float caloriesPer100 = ui->tableWidget->item(row, 3)->text().toFloat();

        // Tính toán số calo thực tế
        float caloriesConsumed = (quantity / 100.0) * caloriesPer100;

        // Thêm dữ liệu vào bảng CALO_IN
        QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
        QString queryString = "INSERT INTO CALO_IN (Ngay, MaTP, So_luong, Calo_thuc_nap) VALUES (:date, :foodId, :quantity, :calories)";
        QSqlQuery query(mydb);
        query.prepare(queryString);
        query.bindValue(":date", currentDate);
        query.bindValue(":foodId", foodId);
        query.bindValue(":quantity", quantity);
        query.bindValue(":calories", caloriesConsumed);


        if (query.exec()) {
            // Hiển thị thông báo thành công
            QMessageBox::information(this, tr("Thành công"), tr("Thực phẩm đã được thêm vào danh sách."));
        } else {
            // Xử lý lỗi khi thêm dữ liệu vào bảng CALO_IN
            QMessageBox::warning(this, tr("Lỗi"), tr("Không thể thêm dữ liệu."));
            qDebug() << "Khong the chay truy van." << query.lastError();
        }

        //Gọi hàm để update lượng Calo tổng đã nạp
        updateTotalCalories();
    }
}

//Tải DS thực phẩm từ CSDL truyền vào bảng
void FoodTab::loadFoodsFromDatabase()
{
    // Truy vấn cơ sở dữ liệu để lấy dữ liệu thực phẩm
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    QString queryString = "SELECT MaTP, TenTP, Don_vi_tinh, Luong_Calo_moi_100donvi FROM THUCPHAM";
    if (query.exec(queryString)) {
        int row = 0;
        while (query.next()) {
            int foodId = query.value(0).toInt();
            QString foodName = query.value(1).toString();
            QString unit = query.value(2).toString();
            float calories = query.value(3).toFloat();

            // Hiển thị thông tin trong bảng
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(foodId)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(foodName));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(unit));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(calories)));

            // Tạo nút "Thêm" và đặt vào cột bổ sung
            QPushButton* addButton = new QPushButton("Thêm");
                connect(addButton, &QPushButton::clicked, this, &FoodTab::buttonAdd_clicked);
            ui->tableWidget->setCellWidget(row, 4, addButton);

            row++;
        }
    } else {
            qDebug() << "Khong the chay truy van." << query.lastError();
            return;
        }
}

void FoodTab::on_pushButton_clicked()
{
        // Hiển thị hộp thoại yêu cầu nhập thông tin thực phẩm
        QString foodName = QInputDialog::getText(this, "Nhập thông tin thực phẩm", "Tên thực phẩm:");
        QString unit = QInputDialog::getText(this, "Nhập thông tin thực phẩm", "Đơn vị tính:");
        double calo = QInputDialog::getDouble(this, "Nhập thông tin thực phẩm", "Lượng calo mỗi 100 đơn vị:");
        float calories = calo;

        QSqlDatabase& mydb = DatabaseManager::getDatabase();
        QSqlQuery query(mydb);

        QString queryString = "INSERT INTO THUCPHAM (TenTP, Don_vi_tinh, Luong_Calo_moi_100donvi) VALUES (:tenThucPham, :donViTinh, :luongCalo)";
        query.prepare(queryString);
        query.bindValue(":tenThucPham", foodName);
        query.bindValue(":donViTinh", unit);
        query.bindValue(":luongCalo", calories);
        query.exec();

        // Kiểm tra và hiển thị thông báo thành công hoặc không thành công
        if (query.lastError().isValid()) {
            QMessageBox::critical(this, "Lỗi", "Không thể thêm thông tin thực phẩm vào CSDL.");
        } else {
            QMessageBox::information(this, "Thành công", "Đã thêm thông tin thực phẩm vào CSDL.");
        }
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        loadFoodsFromDatabase();
}

