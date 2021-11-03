#ifndef FILECOMMAND_H
#define FILECOMMAND_H

#include <QObject>
#include <QSqlQuery>
#include <QProcess>
#include <QVariant>
#include <QMessageBox>
#include <QSettings>

class FileCommand : public QObject
{
    Q_OBJECT
public:
    FileCommand();

    void init7zipPath();

    QStringList getPassWordList();

    bool unZip(QString zipFile);

private:
    QString _7zipExePath;
    QProcess process;
};

#endif // FILECOMMAND_H
