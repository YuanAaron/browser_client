#include <QCoreApplication>
#include <QtNetwork>

//槽函数：监听到信号时的回调函数
void beFinished()
{
    qDebug() << "beFinished";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //1.发起网络请求
    QUrl url("https://www.baidu.com/");
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    //https访问需要添加
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36");
    QNetworkReply* reply = manager.get(request);
//    qDebug() << reply->readAll();

//    qDebug() << reply->url();
//    qDebug() << reply->isFinished();
//    qDebug() << reply->error();

//    qDebug()<<"QT支持的OpenSSL版本: "<<QSslSocket::sslLibraryBuildVersionString();
//    qDebug() << "系统是否支持OpenSSL: " << QSslSocket::supportsSsl();

    //加入监听机制（QT的信号槽机制）
//    QObject::connect(reply, &QNetworkReply::finished,beFinished); //传参不懂
    QObject::connect(reply, &QNetworkReply::finished,[&](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QString htmlContent =  QString::fromUtf8(data);
            qDebug() << htmlContent;
        }
        else
        {
            qDebug() << "Error: " << reply->errorString();
        }

        // 关闭信号槽机制
        reply->deleteLater();
    });


    //2.提取数据

    //3.存储数据

    return a.exec();
}
