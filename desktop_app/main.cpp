#include "mainwindow.h"


#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int currentYear = 2026;

    MainWindow w;
    w.show();


    return QApplication::exec();
}
