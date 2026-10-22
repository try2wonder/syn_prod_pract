#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worker.h"
#include <vector>
#include <QMainWindow>

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

private slots:
    void on_btn_add_clicked();
    void on_btn_applyFilterShow_clicked();
};


#endif // MAINWINDOW_H
