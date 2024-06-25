#include <QCoreApplication>
#include <QTimer>
#include "HttpAccess.h"
#include "RETool.h"
#include "CSVTool.h"

//爬虫的测试和自动化
//1.定时计划
//2.日志的反馈
//3.存在问题的分析

//爬虫程序的后期维护
//1.增量数据的爬取及爬取频率
//2.爬虫抓取失败的日志分析和调整
//3.正则表达式的调整

//爬虫工程师感觉也不错哦
//python的开源爬虫框架：scrapy、scrapy-redis
//爬虫程序的法律风险问题的讨论：
    //robots协议（https://www.mafengwo.cn/robots.txt）
    //数据的抓取和应用原则

void Exit()
{
    QCoreApplication::exit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //1.发起网络请求
    QUrl url("https://www.baidu.com/");
    HttpAccess httpAccess;

    //正则表达式中的 贪婪与懒惰 参考：https://deerchao.cn/tutorials/regex/regex.htm#greedyandlazy
    //万能表达式：[\s\S]*? 与 .*? 的区别（后者无法包含换行符\n和\r）
    //分组的概念：从匹配到的结果中再取内容，使用()分组得到，如取链接内容和标题内容
    //用postman爬取百度首页才发现的坑：从浏览器中查看到的是<li class="news-meta-item...，但实际爬取到的页面中是<li class="hotsearch-item...。
    //<li class="hotsearch-item.*?href="(.*?)".*?<span class="title-content-title">(.*?)</span>
    //<li class="hotsearch-item[\s\S]*?href="([\s\S]*?)"[\s\S]*?<span class="title-content-title">([\s\S]*?)</span>
    RETool reTool("<li class=\"hotsearch-item[\\s\\S]*?href=\"([\\s\\S]*?)\"[\\s\\S]*?<span class=\"title-content-title\">([\\s\\S]*?)</span>");

    CSVTool csvTool("spider.csv");
    QVector<QString> headers = {"tile","url"};

    QObject::connect(&httpAccess, &HttpAccess::finished, [&](const QString& data){
        //qDebug() << data;
        //2.提取数据
        QVector<QString> results = reTool.Match(data);
        //3.存储数据
        bool isWriteOK = csvTool.WriteCSV(headers, results, "utf-8");
        if(isWriteOK)
        {
            qDebug() << "spider info has been successfully written to csv file.";
        }
        else
        {
            qDebug() << "fail to write spider info to csv file.";
        }
        //读取数据
        QVector<QString> readData = csvTool.ReadCSV("utf-8");
        if (results == readData) {
            qDebug() << "data read from the csv file matches the original test data.";
        } else {
            qDebug() << "data read from the csv file does not match the original test data.";
        }
        //4.exit the app（只有在定时任务（win中通过任务计划程序实现）/命令行手动运行时才有效，在QT运行无效）
        QTimer::singleShot(0,&Exit);
    });
    QObject::connect(&httpAccess, &HttpAccess::error, [](const QString& errorString){
        qDebug() << errorString;
        QTimer::singleShot(0,&Exit);
    });
    httpAccess.Get(url);



    return a.exec();
}
