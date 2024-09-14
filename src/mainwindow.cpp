#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/databasemanager.h"
#include "include/personalinfo.h" // Thêm tên file header của lớp giao diện "PersonalInfo"
#include "include/foodtab.h" // Thêm tên file header của lớp giao diện "FoodTab"
#include "include/btaptab.h"
#include "include/report.h"
#include <QTabWidget>
#include <QMainWindow>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Tạo các đối tượng personalinfo và foodtab
    personalInfo = new PersonalInfo(this);
    foodTab = new FoodTab(this);
    btaptab = new btapTab(this);
    report = new Report(this);

    // Thêm personalinfo và foodtab vào tabWidget
    ui->tabWidget->addTab(personalInfo, "Tôi");
    ui->tabWidget->addTab(foodTab, "Thực phẩm");
    ui->tabWidget->addTab(btaptab, "Bài tập");
    ui->tabWidget->addTab(report, "Báo cáo");

    // Hiển thị tab 1 (personalinfo) mặc định
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
