#ifndef FOODTAB_H
#define FOODTAB_H

#include <QDialog>
#include <QtSql>
#include <include/food_calo_in.h>

namespace Ui {
class FoodTab;
}

class FoodTab : public QDialog
{
    Q_OBJECT

public:
    explicit FoodTab(QWidget *parent = nullptr);
    ~FoodTab();

private slots:
    void on_detailButton_clicked();
    void buttonAdd_clicked();
    void loadFoodsFromDatabase();
    void updateTotalCalories();


    void on_pushButton_clicked();

private:
    Ui::FoodTab *ui;
    QSqlDatabase mydb;
    food_calo_in m_food_calo_in;
};

#endif // FOODTAB_H
