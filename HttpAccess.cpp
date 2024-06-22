#include "HttpAccess.h"

HttpAccess::HttpAccess(QObject *parent) : QObject(parent)
{

}

HttpAccess::~HttpAccess()
{

}

void HttpAccess::Get(const QUrl &url)
{
    QNetworkRequest request(url);
    //https访问需要添加
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36");
    QNetworkReply* reply = m_manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished,[this,reply](){
        qDebug() << reply->error();
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            //TODO: convert the html code
            QString htmlContent = QString::fromUtf8(data);
            //获取到数据后，通过信号将数据二次传递（转发）到外部
            emit finished(htmlContent);
        }
        else
        {
            //获取数据失败，将对应的错误转发到外部
            emit error(reply->errorString());
        }
    });
}
