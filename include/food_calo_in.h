#ifndef FOOD_CALO_IN_H
#define FOOD_CALO_IN_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class food_calo_in;
}

class food_calo_in : public QDialog
{
    Q_OBJECT

public:
    explicit food_calo_in(QWidget *parent = nullptr);
    ~food_calo_in();
    void loadCaloFromDatabase();
    void clearTable();

signals:
    ////
    void closed();

private slots:
    void on_pushButton_clicked();



private:
    Ui::food_calo_in *ui;
    QSqlDatabase mydb;
};

#endif // FOOD_CALO_IN_H
