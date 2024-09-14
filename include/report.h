#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Report *ui;
    QSqlDatabase mydb;
};

#endif // REPORT_H
