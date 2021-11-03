#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include "filecommand.h"
#include <QMessageBox>

QSqlQuery query;

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::arguments().first().remove("AutoPassWordUnzip.exe") + "password.db");
    if(db.open()){
        query = QSqlQuery(db);
        query.exec("create table if not exists passlist(id INTEGER PRIMARY KEY AUTOINCREMENT,password)");
    }


    if(argc > 1){   //如果带有启动参数，即注册表右键菜单启动
        QString filePath = argv[1];
        FileCommand fileCommand;
        fileCommand.unZip(filePath);
    }else{
        MainWindow w;
        w.show();
        return a.exec();
    }
    return 0;
}
