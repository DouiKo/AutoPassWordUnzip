#ifndef FILECOMMAND_H
#define FILECOMMAND_H

#include <QObject>
#include <QSqlQuery>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>

class FileCommand : public QObject
{
    Q_OBJECT
public:
    FileCommand();

    QStringList getPassWordList();

    bool unZip(QString zipFile);

private:
    QString _7zipExePath;
    QProcess process;
};

#endif // FILECOMMAND_H
