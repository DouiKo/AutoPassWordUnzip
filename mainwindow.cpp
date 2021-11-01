#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>

extern QSqlQuery query;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPassWordListModel();
    //process.start("& 'C:/Program Files/7-Zip/7z.exe' x -p'acg12.us' 'C:/Users/29856/Desktop/411.rar'");
    connect(&process,&QProcess::readyReadStandardOutput,this,&MainWindow::readyReadStandardOutput);
    process.execute("\"C:/Program Files/7-Zip/7z.exe\" x -pacg12.us C:/Users/29856/Desktop/411.rar");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSavePassWord_clicked()
{
    passWordModel->submitAll();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    passWordModel->insertRow(0);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    passWordModel->removeRow(ui->tableView->currentIndex().row());
}

void MainWindow::readyReadStandardOutput()
{
    qDebug()<<process.readAll();
}

void MainWindow::initPassWordListModel()
{
    passWordModel = new QSqlTableModel(this);
    passWordModel->setTable("passlist");
    passWordModel->select();
    passWordModel->setHeaderData(1,Qt::Orientation::Horizontal,"密码");

    ui->tableView->setModel(passWordModel);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QStringList MainWindow::getPassWordList()
{
    QStringList passWordList;
    query.exec("select * from passlist");
    while(query.next()){
        passWordList.append(query.value(1).toString());
    }
    return passWordList;
}

void MainWindow::unZip()
{
    QStringList passWordList = getPassWordList();

    foreach (auto pass, passWordList) {
        QString program = "C:/Program Files/7-Zip/7z.exe";
        QStringList list("x -p'acg12.us' 'C:/Users/29856/Desktop/411.rar'");
        process.start(program,list);
    }
    //7z x C:\Users\29856\Desktop\test.zip -p123
}
