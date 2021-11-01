#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

QSqlQuery query;

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("password.db");
    if(db.open()){
        query = QSqlQuery(db);
        query.exec("create table if not exists passlist(id INTEGER PRIMARY KEY AUTOINCREMENT,password)");
    }

    MainWindow w;
    w.show();
    return a.exec();
}
