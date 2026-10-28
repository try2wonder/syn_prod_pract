#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Открытие файла JSON
    QString currentPath = QDir::currentPath();
    qDebug() << QStringLiteral("We are here: ") << currentPath;
    QFile file("scraper/scrapes/synergy_all_pages.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error! Couldn't open the file:" << file.errorString();
        return;
    }

    qDebug() << "File is open. Reading...";
    QByteArray jsonData = file.readAll();
    file.close();


    //QByteArray в JSON классы
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()){
        qDebug() << "Error! json is bricked or wrong format.";
        return;
    }
    QJsonObject rootObject = doc.object();
    qDebug() << "JSON is successfully parsed! Route keys:" << rootObject.keys().size();

    QJsonValue employeesValue = rootObject["/sveden/employees"];


    //Выводим даннные по ключу employees

    if (employeesValue.isObject()){
        QJsonObject employeesObject = employeesValue.toObject();

        QStringList tableNames = employeesObject.keys();

        employeesObject = employeesValue.toObject();
        this->employeesData = employeesObject;

        qDebug() << "Tables found: " << tableNames.size();

        ui->cb_tables->clear();

        ui->cb_tables->addItems(tableNames);

    }





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
    int filterExp = ui->le_userFilterExp->text().toInt();
    ui->tableWidget_workers->setRowCount(0);
    bool isFound = false;
    for (const Worker& worker : workers){
        if (worker.getExperience(2026) > filterExp){
            int row = ui->tableWidget_workers->rowCount();
            ui->tableWidget_workers->insertRow(row);
            ui->tableWidget_workers->setItem(row, 0, new QTableWidgetItem(worker.getFio()));
            ui->tableWidget_workers->setItem(row, 1, new QTableWidgetItem(worker.getPosition()));
            ui->tableWidget_workers->setItem(row, 2, new QTableWidgetItem(QString::number(worker.getSalary())));
            ui->tableWidget_workers->setItem(row, 3, new QTableWidgetItem(QString::number(worker.getFirstYear())));
            isFound = true;
        }
    }
    if (!isFound){
        QMessageBox::information(this,"Поиск","Работников с таким опытом не найдено!");
    }
}

void MainWindow::on_cb_tables_currentTextChanged(const QString &arg1){
    QJsonArray tableArray = employeesData[arg1].toArray();
    ui->tableWidget_json->setRowCount(0);
    ui->tableWidget_json->setColumnCount(0);
    if (tableArray.isEmpty()) return;
    QJsonObject firstRow = tableArray[0].toObject();
    QStringList headers = firstRow.keys();

    ui->tableWidget_json->setColumnCount(headers.size());
    ui->tableWidget_json->setHorizontalHeaderLabels(headers);



    for(int i=0; i < tableArray.size(); ++i){
        QJsonObject rowObject = tableArray[i].toObject();

        ui->tableWidget_json->insertRow(i);

        for (int j = 0; j < headers.size(); ++j){
            QString columnName = headers[j];
            QString cellValue = rowObject[columnName].toString();

            ui->tableWidget_json->setItem(i, j, new QTableWidgetItem(cellValue));
        }
    }
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