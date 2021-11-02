#include "filecommand.h"

extern QSqlQuery query;

FileCommand::FileCommand()
{
    _7zipExePath = "\"C:/Program Files/7-Zip/7z.exe\"";
}

QStringList FileCommand::getPassWordList()
{
    QStringList passWordList;
    query.exec("select * from passlist");
    while(query.next()){
        passWordList.append(query.value(1).toString());
    }
    return passWordList;
}

bool FileCommand::unZip(QString zipFile)
{
    QStringList passWordList = getPassWordList();

    int exitCode = -2;   //0解压完成、-2错误

    while (exitCode != 0) {
        if (passWordList.size() != 0) {
            QString arg = _7zipExePath + " x -p" + passWordList.first() + " " + zipFile;
            exitCode = process.execute(arg);
            passWordList.removeFirst();
        }else{
            //没有正确密码
            QMessageBox::information(nullptr,"错误","字典中没有正确密码");
            return false;
        }
    }
    return true;
}
