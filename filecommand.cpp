#include "filecommand.h"
#include <QDebug>

extern QSqlQuery query;

FileCommand::FileCommand()
{
    init7zipPath();
}

void FileCommand::init7zipPath()
{
    _7zipExePath = "";
    QSettings setting("HKEY_LOCAL_MACHINE\\SOFTWARE\\7-Zip",QSettings::NativeFormat);
    QString path = setting.value("Path64").toString();
    if(path.isEmpty()){
        path = setting.value("Path").toString();
    }
    if(!path.isEmpty()){
        _7zipExePath += "\"";
        _7zipExePath += path;
        _7zipExePath += "7z.exe\"";
    }
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
            QString arg = _7zipExePath + " x -p" + passWordList.first() + " -y " + zipFile;
            exitCode = process.execute(arg);
            passWordList.removeFirst();
        }else{
            //没有正确密码
            QMessageBox::information(nullptr,"失败","字典中没有正确密码");
            return false;
        }
    }
    return true;
}
