#include "RETool.h"

QVector<QString> RETool::Match(const QString &input) const
{
    QVector<QString> res;
    QRegularExpression regex(m_pattern);
    QRegularExpressionMatchIterator iterator = regex.globalMatch(input);
    while(iterator.hasNext())
    {
        QRegularExpressionMatch match = iterator.next();
        res.append(match.captured(2)+":"+match.captured(1));
    }
    return res; //RVO优化
}
