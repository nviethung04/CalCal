#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

signals:
    void saveButtonClicked(); // Tín hiệu khi người dùng nhấn nút "Lưu"

private slots:
    void onSaveButtonClicked();

private:
    Ui::InputDialog *ui;
    QSqlDatabase mydb;
};

#endif // INPUTDIALOG_H
