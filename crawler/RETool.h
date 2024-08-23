#ifndef RETOOL_H
#define RETOOL_H

#include <QVector>
#include <QString>
#include <QRegularExpression>

class RETool
{
public:
    explicit RETool(const QString& pattern = ""):m_pattern(pattern) {};

    QVector<QString> Match(const QString& input) const;
private:
    QString m_pattern;
};

#endif // RETOOL_H
