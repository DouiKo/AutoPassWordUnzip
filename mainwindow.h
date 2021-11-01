#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSavePassWord_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void readyReadStandardOutput();

private:
    void initPassWordListModel();

    QStringList getPassWordList();

    void unZip();

private:
    QProcess process;
    QSqlTableModel *passWordModel;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
