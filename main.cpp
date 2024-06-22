#include <QCoreApplication>
#include "HttpAccess.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //1.发起网络请求
    QUrl url("https://www.baidu.com/");
    HttpAccess httpAccess;
    QObject::connect(&httpAccess, &HttpAccess::finished, [](const QString& data){
        qDebug() << data;
    });
    QObject::connect(&httpAccess, &HttpAccess::error, [](const QString& errorString){
        qDebug() << errorString;
    });
    httpAccess.Get(url);

    //2.提取数据

    //3.存储数据

    return a.exec();
}
