#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_workers->setHorizontalHeaderLabels({"ФИО", "Должность", "Зарплата", "Год приема"});
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: on_btn_add_clicked(){

    QString fio = ui->le_fio->text();
    QString position = ui->le_position->text();
    int salary = ui->le_salary->text().toInt();
    int year = ui->le_firstYear->text().toInt();
    Worker newWorker(fio, position, salary, year);
    workers.push_back(newWorker);

    int row = ui->tableWidget_workers->rowCount();
    ui->tableWidget_workers->insertRow(row);
    ui->tableWidget_workers->setItem(row, 0, new QTableWidgetItem(fio));
    ui->tableWidget_workers->setItem(row, 1, new QTableWidgetItem(position));
    ui->tableWidget_workers->setItem(row, 2, new QTableWidgetItem(QString::number(salary)));
    ui->tableWidget_workers->setItem(row, 3, new QTableWidgetItem(QString::number(year)));

    ui->le_fio->clear();
    ui->le_position->clear();
    ui->le_salary->clear();
    ui->le_firstYear->clear();

}

void MainWindow::on_btn_applyFilterShow_clicked()
{
    // Пока здесь пусто. Мы напишем логику фильтрации чуть позже.
    // Но теперь компилятор счастлив, ведь он нашел эту функцию!
}
/*
[
  {
    "fio": "Иванов И.И.",
    "position": "Разработчик",
    "salary": 150000,
    "firstYear": 2018
  }
]
*/