#include "include/personalinfo.h"
#include "ui_personalinfo.h"
#include "include/inputdialog.h"
#include "include/databasemanager.h"

PersonalInfo::PersonalInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalInfo)
{
    ui->setupUi(this);

    QSqlDatabase& mydb = DatabaseManager::getDatabase();

    if (!mydb.open())
        ui->dbstatus->setText("Can't connect!");
    else
        ui->dbstatus->setText("Connected...");

    updatePersonalInfoFromDatabase();

}

PersonalInfo::~PersonalInfo()
{
    delete ui;
}

void PersonalInfo::setUserName(const QString& name)
{
    ui->nameLabel->setText(name);
}

void PersonalInfo::setAge(int age)
{
    ui->ageLabel->setText(QString::number(age));
}

void PersonalInfo::setHeight(int height)
{
    ui->heightLabel->setText(QString::number(height));
}

void PersonalInfo::setWeight(int weight)
{
    ui->weightLabel->setText(QString::number(weight));
}

void PersonalInfo::setGender(const QString& gender)
{
    ui->genderLabel->setText(gender);
}

void PersonalInfo::setBMI(float bmi)
{
    ui->bmiLabel->setText(QString::number(bmi));
}

void PersonalInfo::setBodyStatus(const QString& bodyStatus)
{
    ui->bodyLabel->setText(bodyStatus);
}

void PersonalInfo::setGoal(int Goal)
{
    ui->goalLabel->setText(QString::number(Goal));
}

void PersonalInfo::setRecommendation(const QString& recommendation)
{
    ui->recommendationLabel->setText(recommendation);
}

void PersonalInfo::updatePersonalInfoFromDatabase()
{
    QSqlDatabase& mydb = DatabaseManager::getDatabase();
    QSqlQuery query(mydb);
    query.prepare("SELECT name, age, height, weight, gender, bmi, body_type, recommendation, goal FROM NGUOIDUNG ORDER BY ROWID DESC LIMIT 1");

    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        int age = query.value(1).toInt();
        int height = query.value(2).toInt();
        int weight = query.value(3).toInt();
        QString gender = query.value(4).toString();
        float bmi = query.value(5).toFloat();
        QString body_type = query.value(6).toString();
        QString recommendation = query.value(7).toString();
        int goal = query.value(8).toInt();

        setUserName(name);
        setAge(age);
        setHeight(height);
        setWeight(weight);
        setGender(gender);
        setBMI(bmi);
        setBodyStatus(body_type);
        setRecommendation(recommendation);
        setGoal(goal);
    } else {
        ui->dbstatus->setText("Chưa có thông tin hoặc không kết nối được CSDL.");
        // Có thể hiển thị một thông báo hoặc xử lý theo ý của bạn
    }
}


void PersonalInfo::on_editButton_clicked()
{
    // Mở giao diện InputDialog
    InputDialog inputDialog;
    inputDialog.setModal(true);
    inputDialog.exec();

    // Sau khi InputDialog đóng, cập nhật thông tin cá nhân từ cơ sở dữ liệu
    updatePersonalInfoFromDatabase();
}

