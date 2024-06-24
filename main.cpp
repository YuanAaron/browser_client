#include <QCoreApplication>
#include "HttpAccess.h"
#include "RETool.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //1.发起网络请求
    QUrl url("https://www.baidu.com/");
    HttpAccess httpAccess;

    //正则表达式中的 贪婪与懒惰 参考：https://deerchao.cn/tutorials/regex/regex.htm#greedyandlazy
    //万能表达式：[\s\S]*? 与 .*? 的区别（后者无法包含换行符\n和\r）
    //分组的概念：从匹配到的结果中再取内容，使用()，如取链接内容和标题内容
    //用postman爬取百度首页才发现的坑：从浏览器中查看到的是<li class="news-meta-item...，但实际爬取到的页面中是<li class="hotsearch-item...。
    //<li class="hotsearch-item.*?href="(.*?)".*?<span class="title-content-title">(.*?)</span>
    //<li class="hotsearch-item[\s\S]*?href="([\s\S]*?)"[\s\S]*?<span class="title-content-title">([\s\S]*?)</span>
    RETool reTool("<li class=\"hotsearch-item[\\s\\S]*?href=\"([\\s\\S]*?)\"[\\s\\S]*?<span class=\"title-content-title\">([\\s\\S]*?)</span>");

    QObject::connect(&httpAccess, &HttpAccess::finished, [&](const QString& data){
        //qDebug() << data;
        //2.提取数据
        QVector<QString> results = reTool.Match(data);
        for(const QString& res: results)
        {
            qDebug() << res;
        }

    });
    QObject::connect(&httpAccess, &HttpAccess::error, [](const QString& errorString){
        qDebug() << errorString;
    });
    httpAccess.Get(url);

    //3.存储数据

    return a.exec();
}
