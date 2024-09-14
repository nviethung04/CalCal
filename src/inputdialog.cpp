#include "include/inputdialog.h"
#include "ui_inputdialog.h"
#include "include/databasemanager.h"
#include "include/mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    QSqlDatabase& mydb = DatabaseManager::getDatabase();

    if (!mydb.open())
        ui->dbstatus->setText("Can't connect!");
    else
        ui->dbstatus->setText("Connected...");

    ui->weightspinBox->setMaximum(999);
    ui->goalspinBox->setMaximum(999);
    ui->heightspinBox->setMaximum(999);
    ui->agespinBox->setMaximum(999);

    connect(ui->saveButton, &QPushButton::clicked, this, &InputDialog::onSaveButtonClicked);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::onSaveButtonClicked()
{

    QString name = ui->nameLineEdit->text();
    int age = ui->agespinBox->value();
    int height = ui->heightspinBox->value();
    int weight = ui->weightspinBox->value();
    int goal = ui->goalspinBox->value();
    QString gender = ui->gendercomboBox->currentText();

    if (name.isEmpty() || age == 0 || height == 0 || weight == 0) {
        QMessageBox::warning(this, "Thông báo", "Bạn cần nhập đủ các thông tin.");
        return;
    }

    // Tính toán chỉ số BMI
    float bmi = weight / ((height / 100.0f) * (height / 100.0f));


    // Phân loại thể trạng
    QString bodyType;
    if (bmi < 18.5) {
        bodyType = "Gầy";
    } else if (bmi < 24.9) {
        bodyType = "Bình thường";
    } else if (bmi < 29.9) {
        bodyType = "Hơi béo";
    } else {
        bodyType = "Béo phì";
    }


    // Lượng calories khuyến nghị
    int minCalories = 0;
    int maxCalories = 0;
    if (gender == "Nam") {
        minCalories = 66 + (13.75 * weight) + (5 * height) - (6.75 * age);
        maxCalories = minCalories + 500;
    } else {
        minCalories = 655 + (9.56 * weight) + (1.85 * height) - (4.68 * age);
        maxCalories = minCalories + 500;
    }

    QString calorieRecommendation = QString("Lượng calories tối thiểu bạn nên nạp hàng ngày là %1. "
                                            "Lượng calories tối đa nên ít hơn %2. ")
                                        .arg(minCalories).arg(maxCalories);

    // Khuyến cáo
    QString recommendation;
    if (bodyType == "Gầy") {
        recommendation = "Với thể trạng hiện tại, chúng tôi kiến nghị bạn nên tăng cân. " + calorieRecommendation;
    } else if (bodyType == "Bình thường") {
        recommendation = "Với thể trạng hiện tại, chúng tôi kiến nghị bạn nên duy trì cân nặng. " + calorieRecommendation;
    } else {
        recommendation = "Với thể trạng hiện tại, chúng tôi kiến nghị bạn nên giảm cân. "+ calorieRecommendation;
    }


    // Lưu thông tin vào cơ sở dữ liệu
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    query.prepare("INSERT INTO NGUOIDUNG (name, age, height, weight, gender, bmi, body_type, recommendation, goal) "
                  "VALUES (:name, :age, :height, :weight, :gender, :bmi, :body_type, :recommendation, :goal)");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":height", height);
    query.bindValue(":weight", weight);
    query.bindValue(":gender", gender);
    query.bindValue(":bmi", bmi);
    query.bindValue(":body_type", bodyType);
    query.bindValue(":recommendation", recommendation);
    query.bindValue(":goal", goal);


    if (!query.exec()) {
        QMessageBox::warning(this, "Lỗi", "Không thể thêm người dùng vào cơ sở dữ liệu.");
        qDebug() << "Khong the chay truy van." << query.lastError();
        return;
    }
    else {
        emit saveButtonClicked(); // Kích hoạt tín hiệu saveButtonClicked
        close();
    }
}
