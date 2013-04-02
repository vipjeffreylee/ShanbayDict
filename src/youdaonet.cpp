#include "src/youdaonet.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "dict.h"

YoudaoNet::YoudaoNet(QObject *parent) :
    QObject(parent)
{
    http=new QNetworkAccessManager(this);
    connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpfinished(QNetworkReply*)));
}
void YoudaoNet::queryWord(const QString &word){
    QNetworkRequest request;
    QString urlstr=QString("http://fanyi.youdao.com/openapi.do?keyfrom=qtcnorg&key=624498262&type=data&doctype=json&version=1.1&q=%1").arg(word);
    request.setUrl(QUrl(urlstr));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    http->get(request);
}

void YoudaoNet::httpfinished(QNetworkReply* reply){
    qDebug()<<"end youdao!!!!!";
    //qDebug()<<reply->errorString()<<QString::fromUtf8(reply->readAll());
    QJsonDocument jsonDoc;
    QJsonObject jsonObj,basicObj;
    QJsonValue jsonValue;
    jsonDoc=QJsonDocument::fromJson(reply->readAll());
    if(!jsonDoc.isNull()){
        jsonObj=jsonDoc.object();
        qDebug()<<jsonObj;
        if(jsonObj.value("errorCode").toDouble()==0){
            DICT::word->youdaoWord+=QString("<font color='blue'><b>%1. </b></font>  ").arg(jsonObj.value("query").toString());
            DICT::word->youdaoWord+="<font color='black'><b>";
            foreach(auto value,jsonObj.value("translation").toArray()){
                DICT::word->youdaoWord+=value.toString();
            }
            jsonValue=jsonObj.value("basic");
            if(!jsonValue.isUndefined()){
                basicObj=jsonValue.toObject();
                foreach(auto value,basicObj.value("explains").toArray()){
                    DICT::word->youdaoWord+=value.toString();
                }
            }
            DICT::word->youdaoWord+="</b></font><br>";
            DICT::word->youdaoWord+="<font color='gray'>---------------------------------------------网络释义---------------------------------------------</font><br>";
            foreach(auto value,jsonObj.value("web").toArray()){
                QJsonObject o=value.toObject();
                DICT::word->youdaoWord+=QString("<font color='blue'><b>%1. </b></font>  ").arg(o.value("key").toString());
                foreach(auto v,o.value("value").toArray()){
                    DICT::word->youdaoWord+=QString("<font color='black'><b>%1. </b></font> ").arg(v.toString());
                }
                DICT::word->youdaoWord+="<br>";
            }

        }else{
            DICT::word->youdaoWord=tr("错误代码：%1").arg(jsonObj.value("errorCode").toDouble());
        }
        qDebug()<<DICT::word->youdaoWord;
    }
    emit signalQueryFinished();
}
