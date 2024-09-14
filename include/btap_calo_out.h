#ifndef BTAP_CALO_OUT_H
#define BTAP_CALO_OUT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class btap_calo_out;
}

class btap_calo_out : public QDialog
{
    Q_OBJECT

public:
    explicit btap_calo_out(QWidget *parent = nullptr);
    ~btap_calo_out();
    void loadCaloFromDatabase();
    void clearTable();

signals:
    ////
    void closed();

private slots:
    void on_pushButton_clicked();



private:
    Ui::btap_calo_out *ui;
    QSqlDatabase mydb;
};

#endif // BTAP_CALO_OUT_H
