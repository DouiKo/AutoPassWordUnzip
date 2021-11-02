#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "filecommand.h"

//Bug
//1、同目录下如已有同名解压好的文件，程序将死循环

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPassWordListModel();
    setWindowTitle("自动密码解压");
    setWindowIcon(QIcon(":/i/zip.ico"));
    //process.start("& 'C:/Program Files/7-Zip/7z.exe' x -p'acg12.us' 'C:/Users/29856/Desktop/411.rar'");
    //connect(&process,&QProcess::readyReadStandardOutput,this,&MainWindow::readyReadStandardOutput);
    //process.start("\"C:/Program Files/7-Zip/7z.exe\" x -p1213 C:/Users/29856/Desktop/ceshi.7z");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSavePassWord_clicked()
{
    passWordModel->submitAll();
    passWordModel->select();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    passWordModel->insertRow(0);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    passWordModel->removeRow(ui->tableView->currentIndex().row());
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

