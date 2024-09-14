#ifndef BTAPTAB_H
#define BTAPTAB_H

#include <QDialog>
#include <QtSql>
#include <include/btap_calo_out.h>

namespace Ui {
class btapTab;
}

class btapTab : public QDialog
{
    Q_OBJECT

public:
    explicit btapTab(QWidget *parent = nullptr);
    ~btapTab();

private slots:
    void on_detailButton_clicked();
    void buttonAdd_clicked();
    void loadFromDatabase();
    void updateTotalCalories();


private:
    Ui::btapTab *ui;
    QSqlDatabase mydb;
    btap_calo_out m_btap_calo_out;
};

#endif // BTAPTAB_H
