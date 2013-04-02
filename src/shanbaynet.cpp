/****************************************************************************
**
** Copyright (C) 2013 Jeffrey Lee.
** All rights reserved.
** Contact: vipjeffreylee@gmail.com
**
** This file is part of the ShanbayDict.
**
** $BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
**
**
** $END_LICENSE$
**
****************************************************************************/
#include "shanbaynet.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "dict.h"
ShanbayNet::ShanbayNet(QObject *parent) :
    QObject(parent)
{
    http=new QNetworkAccessManager(this);
    http->setCookieJar(new QNetworkCookieJar(this));
    connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpfinished(QNetworkReply*)));
}
ShanbayNet::~ShanbayNet(){
   // delete http;
}

void ShanbayNet::getSessionid(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/accounts/login/"));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::GetSessionidAction;
    http->get(request);
}

void ShanbayNet::queryWord(const QString &word){
    QNetworkRequest request;
    queryword=word;
    request.setUrl(QUrl("http://www.shanbay.com/api/word/"+word));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::QueryWordAction;
    //qDebug()<<"Query "+word;
    http->get(request);
}
void ShanbayNet::queryExamples(QString learningid){
    if(learningid=="0"){
        return;
    }
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/learning/examples/"+learningid));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::QueryWordExamplesAction;
    http->get(request);
}

void ShanbayNet::addWord(){

    if(DICT::word->name.isEmpty()){
        emit signalAddwordFinished(false);
        return;
    }
    addWord(DICT::word->name);

}
void ShanbayNet::addWord(const QString &word){
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/learning/add/"+word));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::AddWordAction;
    http->get(request);
}
void ShanbayNet::addExample(QString sentence, QString translation){
    if(DICT::word->learning_id.isNull()||DICT::word->learning_id=="0"){
        emit signalAddExampleFinished("单词没有在你的单词库中，现在不能为该单词添加例句");
        return;
    }
    if(sentence.trimmed().isEmpty()||translation.trimmed().isEmpty()){
        emit signalAddExampleFinished("例句或翻译不能为空");
        return;
    }
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://www.shanbay.com/api/example/add/%1?sentence=%2&translation=%3")
                        .arg(DICT::word->learning_id)
                        .arg(sentence)
                        .arg(translation)));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::AddExampleAction;
    http->get(request);
}

void ShanbayNet::login(const QString &u,const QString &p){
    username=u;
    password=p;
    getSessionid();
}
void ShanbayNet::loginShanbay(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/accounts/login/"));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    request.setRawHeader("Origin","http//www.shanbay.com");
    request.setRawHeader("Referer","http://www.shanbay.com/accounts/login/");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    QByteArray postData;
    postData.append(QString("csrfmiddlewaretoken=%1&").arg(sessionid));
    postData.append(QString("username=%1&password=%2&").arg(QUrl::toPercentEncoding(username).constData()).arg(password));
    //qDebug()<<QString("username=%1&password=%2&").arg(QUrl::toPercentEncoding(username).constData()).arg(password);
    postData.append("login=登录&continue=home&u=1&next=");
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.size());
    httpAction=HttpAction::LoginAction;
    http->post(request,postData);
}

void ShanbayNet::httpfinished(QNetworkReply* reply){
    //        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString().isEmpty()){
    //            qDebug()<<QString::fromUtf8(reply->readAll());
    //        }
    //qDebug()<<QString::fromUtf8(reply->readAll());
    //qDebug()<<"Http request finished!"<<reply->error()<<reply->errorString()<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString()<<reply->url();


    //QVariantMap jsonObj,vocObj,en_definitionsObj,exmObj;
    //QVariantList enList,exmList;
    QJsonDocument jsonDoc;
    QJsonObject jsonObj,vocObj,en_definitionsObj;
    switch(httpAction){
    case HttpAction::NoAction:
        break;
    case HttpAction::GetSessionidAction:
        sessionid=getCookie("csrftoken");
        //qDebug()<<"sessionid="<<sessionid<<reply->readAll();
        if(sessionidOk()){
            emit signalLoginFinished(false,"已经连接扇贝网，正在验证用户名密码...");
            loginShanbay();
        }else{
            emit signalLoginFinished(false,"无法连接扇贝网，请稍后重试");
        }
        break;
    case HttpAction::LoginAction:
        httpAction=HttpAction::NoAction;
        if(0==reply->readAll().size()){
            nickname=QUrl::fromPercentEncoding(getCookie("nickname").toLatin1());
            //qDebug()<<"Login OK!nickname="<<nickname;
            emit signalLoginFinished(true,"登录成功！");
        }else{
            //qDebug()<<"Login failed!";
            emit signalLoginFinished(false,"登录失败！用户名或者密码错误");
        }
        break;
    case HttpAction::QueryWordAction:
        //qDebug()<<"query word";
        //jsondata=jsonParser->parse(reply->readAll(),&jsonok);
        jsonDoc=QJsonDocument::fromJson(reply->readAll());
        if(!jsonDoc.isNull()){
            // jsonObj=jsondata.toMap();
            jsonObj=jsonDoc.object();
            vocObj=jsonObj.value("voc").toObject();
            en_definitionsObj=vocObj.value("en_definitions").toObject();
            DICT::word->clear();
            DICT::word->name=vocObj.value("content").toString();
            DICT::word->learning_id=QString::number(jsonObj.value("learning_id").toDouble(),'g',15);
            DICT::word->definition=vocObj.value("definition").toString();
            DICT::word->pron=vocObj.value("pron").toString();
            DICT::word->audio=vocObj.value("audio").toString();
            //DICT::word->en_definitions="<br>";
            for(auto it=en_definitionsObj.constBegin();it!=en_definitionsObj.constEnd();it++){
                //qDebug()<<it.key()<<it.value();
                DICT::word->en_definitions+=QString("<br><font color='black'><b>%1. </b></font>").arg(it.key());
                if(it.value().isArray()){
                    foreach(QJsonValue jv,it.value().toArray()){
                        DICT::word->en_definitions+=QString("%1; ").arg(jv.toString());
                    }
                }
                DICT::word->en_definitions+="<br>";

            }
//                        qDebug()<<QString("wordname=%1,learning_id=%2,definition=%3,pron=[%4],audio=%5,en_definition=%6")
//                                  .arg(DICT::word->name)
//                                  .arg(DICT::word->learning_id)
//                                  .arg(DICT::word->definition)
//                                  .arg(DICT::word->pron)
//                                  .arg(DICT::word->audio)
//                                  .arg(DICT::word->en_definitions);
            emit signalQueryFinished();
            //qDebug()<<DICT::word->learning_id;
            if(DICT::word->learning_id!="0"){
                queryExamples(DICT::word->learning_id);
            }

            //qDebug()<<jsonObj.value("voc").toMap().value("definition").toString();
            //qDebug()<<jsondata;
        }
        break;
    case HttpAction::AddExampleAction:
        //qDebug()<<QString::fromUtf8(reply->readAll());
        // jsondata=jsonParser->parse(reply->readAll(),&jsonok);
        jsonDoc=QJsonDocument::fromJson(reply->readAll());
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            //qDebug()<<"example_status"<<jsonObj.value("example_status").toString();
            double examplestatus=jsonObj.value("example_status").toDouble();
            if(examplestatus==1){
                emit signalAddExampleFinished("例句添加成功");
            }else if(examplestatus==0){
                emit signalAddExampleFinished("例句添加失败，例句或翻译不能为空");

            }else if(examplestatus==100){
                emit signalAddExampleFinished("例句添加失败，例句未包含指定原词，或者它的有效变体");

            }else if(examplestatus==300){
                emit signalAddExampleFinished("例句添加失败，例句及其译文总长超过300个字符");
            }else{
                emit signalAddExampleFinished("例句添加失败，指定词汇学习记录实例不存在，或者用户无权查看其内容");
            }
        }else{
            emit signalAddExampleFinished("例句添加失败");
        }
        break;
    case HttpAction::QueryWordExamplesAction:
        qDebug()<<"query word examples";
        jsonDoc=QJsonDocument::fromJson(reply->readAll());
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            if(jsonObj.value("examples_status").toDouble()==1){
                foreach(QJsonValue jv,jsonObj.value("examples").toArray()){
                    DICT::word->examples.append(jv.toObject());
                }

                //                auto exmList=jsonObj.value("examples").toList();
                //                for(int i=0;i<exmList.size();i++){
                //                    exmObj=exmList.at(i);
                //                    DICT::word->examples.append(exmObj);
                //                    qDebug()<<exmObj.value("first").toString()+exmObj.value("mid").toString()+exmObj.value("last").toString();
                //                    qDebug()<<exmObj.value("translation").toString();
                //                }
                emit signalQueryExampleFinished();
            }

        }
        break;
    case HttpAction::AddWordAction:
        //qDebug()<<"add word_____________"<<QString::fromUtf8(reply->readAll());


        jsonDoc=QJsonDocument::fromJson(reply->readAll());
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            //qDebug()<<"jsonObj"<<jsonObj;
            DICT::word->learning_id=QString::number(jsonObj.value("id").toDouble(),'g',15);
            qDebug()<<jsonObj.value("id").toDouble()<<"add word result learning id="<<DICT::word->learning_id<< (DICT::word->learning_id!="0");
            emit signalAddwordFinished(DICT::word->learning_id!="0");
            queryExamples(DICT::word->learning_id);
        }
        //qDebug()<<QString::fromUtf8(reply->readAll());
        break;
    default:
        //        qDebug()<<reply->rawHeader("Content-Encoding");//gzip
        //        qDebug()<<QString::fromUtf8(reply->readAll());
        break;

    }

}
QString ShanbayNet::getCookie(const QString &name){
    //qDebug()<<"get cookie";
    foreach(QNetworkCookie cookie , http->cookieJar()->cookiesForUrl(QUrl("http://www.shanbay.com/"))){
        //qDebug()<<cookie.name();
        if(cookie.name()==name){
            return cookie.value();
        }
    }
    return "";
}
