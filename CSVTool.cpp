#include "CSVTool.h"

bool CSVTool::WriteCSV(const QVector<QString> headers,
                       const QVector<QString> &pairs,
                       const char* codecName)
{
    QFile file(m_fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "fail to open file for writing";
        return false;
    }

    QTextStream outFile(&file);
    outFile.setCodec(codecName);

    //write headers and pairs to the csv file with exception
    try {
        //headers
        outFile << headers[0] << " : "<<headers[1] <<"\n";

        //pairs
        for(const QString& pair : pairs)
        {
            QStringList parts =  pair.split(" : ");
            if(parts.size() != 2)
            {
                throw std::runtime_error("data item format is invalid");
            }
            outFile << parts[0] << " : " <<parts[1];
            outFile << "\n";
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        qDebug() << "Error while writing csv: " <<e.what();
        file.close();
        return false;
    }

}

QVector<QString> CSVTool::ReadCSV(const char* codeName)
{
    QVector<QString> data;
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "fail to open file for reading.";
        return data;
    }

    QTextStream in(&file);
    in.setCodec(codeName);

    // read headers from the csv file
    QString headerLine = in.readLine();
    // read data rows from the csv file
    while (!in.atEnd())
    {
        QString dataLine = in.readLine();
        data.append(dataLine);
    }

    file.close();
    return data;
}
