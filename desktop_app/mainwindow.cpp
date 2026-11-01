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
#include <QProcess>
#include <QProcessEnvironment>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadJsonData();
    ui->tableWidget_workers->setHorizontalHeaderLabels({    "Ф.И.О.",
                                                        "Должность преподавателя",
                                                        "Перечень преподаваемых дисциплин",
                                                        "Уровень профессионального образования",
                                                        "Ученая степень",
                                                        "Ученое звание",
                                                        "Повышение квалификации",
                                                        "Профессиональная переподготовка",
                                                        "Опыт",
                                                        "Образовательных программы"});



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadJsonData(){

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
    fullJsonData = doc.object();
    qDebug() << "JSON is successfully parsed! Route keys:" << fullJsonData.keys().size();

    QStringList pageKeys = fullJsonData.keys();
    ui->cb_pages->clear();
    ui->cb_pages->addItems(pageKeys);


    if (!pageKeys.isEmpty()){
        on_cb_pages_currentTextChanged(pageKeys.first());
    }

    ///для вкладки Task3
    ui->cb_tablesEmployees->clear();

    QJsonValue pageValue = fullJsonData["/sveden/employees"];

    if (pageValue.isObject()){
        QJsonObject pageObj = pageValue.toObject();
        QStringList tableNames = pageObj.keys();
        qDebug() << "Tables found: " << tableNames.size();
        ui->cb_tablesEmployees->addItems(tableNames);
    }

}

void MainWindow::on_btn_add_clicked()
{

    QString fio = ui->le_fio->text();
    QString position = ui->le_position->text();
    QString experience = ui->le_experience->text();
    QString disciplines = ui->le_disciplines->text();
    QString educationLevel = ui->le_educationLevel->text();
    QString academicDegree = ui->le_academicDegree->text();
    QString academicTitle = ui->le_academicTitle->text();
    QString qualificationImprovement = ui->le_qualificationImprovement->text();
    QString professionalRetraining = ui->le_professionalRetraining->text();
    QString educationalPrograms = ui->le_educationalPrograms->text();

    if(fio.isEmpty()){
        qDebug() << "No credentials entered. Creating a default worker.";

        Worker defaultWorker;
        workers.push_back(defaultWorker);

        fio = defaultWorker.getFio();
        position = defaultWorker.getPosition();
        experience = defaultWorker.getExperience();
        disciplines = defaultWorker.getDisciplines();
        educationLevel = defaultWorker.getEducationLevel();
        academicDegree = defaultWorker.getAcademicDegree();
        academicTitle = defaultWorker.getAcademicTitle();
        qualificationImprovement = defaultWorker.getQualificationImprovement();
        professionalRetraining = defaultWorker.getProfessionalRetraining();
        educationalPrograms = defaultWorker.getEducationalPrograms();

    }
    else {
        Worker newWorker(fio,
                         position,
                         disciplines,
                         educationLevel,
                         academicDegree,
                         academicTitle,
                         qualificationImprovement,
                         professionalRetraining,
                         experience,
                         educationalPrograms
                         );
        workers.push_back(newWorker);
    }


    int row = ui->tableWidget_workers->rowCount();
    ui->tableWidget_workers->insertRow(row);
    ui->tableWidget_workers->setItem(row, 0, new QTableWidgetItem(fio));
    ui->tableWidget_workers->setItem(row, 1, new QTableWidgetItem(position));
    ui->tableWidget_workers->setItem(row, 2, new QTableWidgetItem(disciplines));
    ui->tableWidget_workers->setItem(row, 3, new QTableWidgetItem(educationLevel));
    ui->tableWidget_workers->setItem(row, 4, new QTableWidgetItem(academicDegree));
    ui->tableWidget_workers->setItem(row, 5, new QTableWidgetItem(academicTitle));
    ui->tableWidget_workers->setItem(row, 6, new QTableWidgetItem(qualificationImprovement));
    ui->tableWidget_workers->setItem(row, 7, new QTableWidgetItem(professionalRetraining));
    ui->tableWidget_workers->setItem(row, 8, new QTableWidgetItem(experience));
    ui->tableWidget_workers->setItem(row, 9, new QTableWidgetItem(educationalPrograms));

    ui->le_fio->clear();
    ui->le_position->clear();
    ui->le_experience->clear();
    ui->le_disciplines->clear();
    ui->le_educationLevel->clear();
    ui->le_academicDegree->clear();
    ui->le_academicTitle->clear();
    ui->le_qualificationImprovement->clear();
    ui->le_professionalRetraining->clear();
    ui->le_educationalPrograms->clear();
}

void MainWindow::on_btn_applyFilterShow_clicked() //<<<<<< пофикси фильтр
{
    // int filterExp = ui->le_userFilterExp->text().toInt();
    // ui->tableWidget_workers->setRowCount(0);
    // bool isFound = false;
    // for (const Worker& worker : workers){
    //     if (worker.getExperience(2026) > filterExp){
    //         int row = ui->tableWidget_workers->rowCount();
    //         ui->tableWidget_workers->insertRow(row);
    //         ui->tableWidget_workers->setItem(row, 0, new QTableWidgetItem(worker.getFio()));
    //         ui->tableWidget_workers->setItem(row, 1, new QTableWidgetItem(worker.getPosition()));
    //         ui->tableWidget_workers->setItem(row, 2, new QTableWidgetItem(QString::number(worker.getSalary())));
    //         ui->tableWidget_workers->setItem(row, 3, new QTableWidgetItem(QString::number(worker.getFirstYear())));
    //         isFound = true;
    //     }
    // }
    // if (!isFound){
    //     QMessageBox::information(this,"Поиск","Работников с таким опытом не найдено!");
    // }
}

void MainWindow::on_btn_loadJsonToWorkers_clicked()
{
    QJsonObject pageObj = fullJsonData["/sveden/employees"].toObject();
    QStringList tableNames = pageObj.keys();
    if (!tableNames.isEmpty()) {
        QString firstTableName = tableNames.first();
        populateTableFromJsonEmployees(ui->tableWidget_workers, "/sveden/employees", firstTableName);

        qDebug() << "JSON is loaded to tableWidget_workers!";
    } else {
        qDebug() << "Tables not found!";
    }
}

void MainWindow::on_cb_pages_currentTextChanged(const QString &arg1){
    ui->cb_tables->clear();

    QJsonValue pageValue = fullJsonData[arg1];

    if (pageValue.isObject()){
        QJsonObject pageObj = pageValue.toObject();
        QStringList tableNames = pageObj.keys();
        qDebug() << "Tables found: " << tableNames.size();
        ui->cb_tables->addItems(tableNames);
    }
}

void MainWindow::on_cb_tables_currentTextChanged(const QString &arg1){
    QString currentPage = ui->cb_pages->currentText();

    populateTableFromJson(ui->tableWidget_json, currentPage, arg1);
}

void MainWindow::populateTableFromJson(QTableWidget *table, const QString &pageUrl, const QString &tableName){
    QJsonObject pageObj = fullJsonData[pageUrl].toObject();
    QJsonArray tableArray = pageObj[tableName].toArray();

    table->setRowCount(0);
    table->setColumnCount(0);

    if (tableArray.isEmpty()) return;

    QJsonObject firstRow = tableArray[0].toObject();
    QStringList headers = firstRow.keys();
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < tableArray.size(); ++i) {
        QJsonObject rowObject = tableArray[i].toObject();
        table->insertRow(i);

        for (int j = 0; j < headers.size(); ++j) {
            QString columnName = headers[j];
            QString cellValue = rowObject[columnName].toString();
            table->setItem(i, j, new QTableWidgetItem(cellValue));
        }
    }
}

void MainWindow::populateTableFromJsonEmployees(QTableWidget *table, const QString &pageUrl, const QString &tableName)
{
    QJsonObject pageObj = fullJsonData[pageUrl].toObject();
    QJsonArray tableArray = pageObj[tableName].toArray();

    table->setRowCount(0);
    table->setColumnCount(0);

    if (tableArray.isEmpty()) return;

    QStringList headers;
    headers << "Ф.И.О."
            << "Должность преподавателя"
            << "Перечень преподаваемыхдисциплин"
            << "Уровень (уровни) профессионального образования, квалификация"
            << "Ученая степень (при наличии)"
            << "Ученое звание (при наличии)"
            << "Сведения о повышение квалификации (за последние 3 года)"
            << "Сведения о профессиональной переподготовке (при наличии)"
            << "Сведения о продолжительности опыта (лет) работы в профессиональной сфере"
            << "Наименование образовательных программ, в реализации которых участвует педагогический работник";

    //Тут бы сделать проверку на наличие заголовков

    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < tableArray.size(); ++i) {
        QJsonObject rowObject = tableArray[i].toObject();
        table->insertRow(i);

        for (int j = 0; j < headers.size(); ++j) {
            QString columnName = headers[j];
            QString cellValue = rowObject[columnName].toString();
            table->setItem(i, j, new QTableWidgetItem(cellValue));
        }
    }
}

void MainWindow::on_cb_tablesEmployees_currentTextChanged(const QString &arg1){
    QString currentPage = "/sveden/employees";
    populateTableFromJsonEmployees(ui->tableWidget_workers, currentPage, arg1);
}

void MainWindow::on_btn_updateData_clicked()
{

    QString pythonPath = "../scraper/.scraperVenv/Scripts/python.exe";
    QString scriptPath = "../scraper/selenHelper.py";
    QString workingDir = "../scraper/";


    QProcess *process = new QProcess(this);

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PYTHONIOENCODING", "utf-8");
    env.insert("PYTHONUTF8", "1");
    process->setProcessEnvironment(env);

    process->setWorkingDirectory(workingDir);

    ui->btn_updateData->setEnabled(false);
    ui->btn_updateData->setText("Парсинг... Пожалуйста, подождите");

    connect(process, &QProcess::readyReadStandardOutput, [process]() {
        QByteArray output =  process->readAllStandardOutput();
        qDebug().noquote() << "Scraper:" << QString::fromUtf8(output);
    });
    connect(process, &QProcess::readyReadStandardError, [process]() {
        QByteArray errorOutput = process->readAllStandardError();
        qDebug() << "Scraper Error:" << QString::fromUtf8(errorOutput);
    });

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [this, process](int exitCode, QProcess::ExitStatus exitStatus) {

                ui->btn_updateData->setEnabled(true);
                ui->btn_updateData->setText("Обновить данные с сайта");

                if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                    QMessageBox::information(this, "Успех", "Данные с сайта успешно обновлены!");

                    loadJsonData();

                } else {
                    QMessageBox::warning(this, "Ошибка", "Скрейпер завершился с ошибкой. Проверьте консоль.");
                }

                process->deleteLater();
            });

    qDebug() << "Launching Script...";
    process->start(pythonPath, QStringList() << scriptPath);
}
