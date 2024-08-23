#ifndef HTTPACCESS_H
#define HTTPACCESS_H

#include <QObject>
#include <QtNetwork>

class HttpAccess : public QObject
{
    Q_OBJECT
public:
    explicit HttpAccess(QObject *parent = nullptr);

    HttpAccess(const HttpAccess& other) = delete;
    HttpAccess(const HttpAccess&& other) = delete;

    HttpAccess& operator=(const HttpAccess& other) = delete;
    HttpAccess& operator=(const HttpAccess&& other) = delete;

    virtual ~HttpAccess();

    void Get(const QUrl& url); //返回通过信号槽机制实现

signals:
    void finished(const QString& data);
    void error(const QString& errorString);

private:
    QNetworkAccessManager m_manager;

};

#endif // HTTPACCESS_H
