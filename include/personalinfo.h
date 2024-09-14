#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QDialog>
#include <QtSql>
#include <include/personalinfo.h>

namespace Ui {
class PersonalInfo;
}

class PersonalInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalInfo(QWidget *parent = nullptr);
    ~PersonalInfo();

    // Các phương thức để cập nhật thông tin người dùng
    void setUserName(const QString& name);
    void setAge(int age);
    void setHeight(int height);
    void setWeight(int weight);
    void setGender(const QString& gender);
    void setBMI(float bmi);
    void setBodyStatus(const QString& bodyStatus);
    void setGoal(int Goal);
    void setRecommendation(const QString& recommendation);
    void updatePersonalInfoFromDatabase();

private slots:
    void on_editButton_clicked();

private:
    Ui::PersonalInfo *ui;
    QSqlDatabase mydb;
};

#endif // PERSONALINFO_H
