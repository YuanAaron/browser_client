#ifndef CSVTOOL_H
#define CSVTOOL_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <stdexcept>

class CSVTool
{
public:
    explicit CSVTool(const QString& fileName):m_fileName(fileName){};

    bool WriteCSV(const QVector<QString> headers, const QVector<QString>& pairs, const char* codeName);
    QVector<QString> ReadCSV(const char* codeName);

private:
    QString m_fileName;
};

#endif // CSVTOOL_H
