#include "mainwindow.h"
#include "surveywizard.h"
#include <QApplication>
#include <QtSql/QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.open();
    // db.close(); // for close connection

    MainWindow w;
    w.show();

    return a.exec();
}
