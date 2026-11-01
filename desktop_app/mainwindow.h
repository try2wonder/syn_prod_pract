#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worker.h"
#include <vector>
#include <QMainWindow>
#include <QJsonObject>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    std::vector<Worker> workers;
    QJsonObject fullJsonData;

private slots:
    void loadJsonData();
    void on_btn_add_clicked();
    void on_btn_applyFilterShow_clicked();
    void on_cb_tables_currentTextChanged(const QString &arg1);
    void on_cb_pages_currentTextChanged(const QString &arg1);
    void on_btn_updateData_clicked();
    void populateTableFromJson(QTableWidget *table, const QString &pageUrl, const QString &tableName);
    void populateTableFromJsonEmployees(QTableWidget *table, const QString &pageUrl, const QString &tableName);
    void on_btn_loadJsonToWorkers_clicked();
    void on_cb_tablesEmployees_currentTextChanged(const QString &arg1);
};


#endif // MAINWINDOW_H