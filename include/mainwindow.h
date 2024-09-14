#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/personalinfo.h>
#include <include/foodtab.h>
#include <include/btaptab.h>
#include <include/report.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PersonalInfo *personalInfo; // Đối tượng personalinfo
    FoodTab *foodTab; // Đối tượng foodtab
    btapTab *btaptab;
    Report *report;
};

#endif // MAINWINDOW_H
