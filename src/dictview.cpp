
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
****************************************************************************/#include "dictview.h"
#include "ui_dictview.h"
#include <QDebug>
#include <QDir>
#include <QWebFrame>
#include <QDesktopServices>
DictView::DictView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DictView)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    qDebug()<<QUrl::fromLocalFile(QDir::currentPath()+"/dict.htm");
    ui->webView->load(QUrl::fromLocalFile(QDir::currentPath()+"/dict.htm"));

    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    QList<QAction*> actions;
    //ui->webView->pageAction(QWebPage::Copy)->setText(tr("复制"));
    actions<<ui->webView->pageAction(QWebPage::Copy)
          <<ui->webView->pageAction(QWebPage::Paste);
    ui->webView->addActions(actions);
    ui->webView->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(ui->webView,SIGNAL(linkClicked(QUrl)),this,SLOT(linkClicked(QUrl)));

}


DictView::~DictView()
{
    delete ui;
}
void DictView::linkClicked(const QUrl &url){
    qDebug()<<url.toString();
    QString urlstr=url.toString();
    if(urlstr=="dict://speak"){
        emit speakClick();
        return;
    }
    if(urlstr=="dict://addword"){
        emit addwordClick();
        return;
    }
    if(urlstr.startsWith("http://audio.dict.cn/mp3")){
        emit speakWord(urlstr);
        return;
    }
    if(urlstr.startsWith("http://")){
        QDesktopServices::openUrl(url);
        return;
    }
}

void DictView::clear(){
    QString nullstr="";
    setWordNamePron(nullstr);
    setWordDefinition(nullstr);
    setWordExample(nullstr);
    setTipInfo(nullstr);
    showSpeak(0);
    showShanbay(0);
}
void DictView::setShanbayNetStatus(int status){

    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("jfSetDictStatus('ShanbayNet_status',%1)").arg(status));
    showShanbay(1);
}


void DictView::setWordNamePron(QString str){
    //ui->webView->setHtml("dddddddddddddddd");
   // qDebug()<<QString("jfSetValue('ShanbayDict_word_namepron',\"%1\");").arg(str);
    //ui->webView->page()->mainFrame()->evaluateJavaScript(QString("alert('hahah');"));
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("jfSetValue('ShanbayDict_word_namepron',\"%1\");").arg(str));
    showSpeak(1);
}

void DictView::setWordDefinition(QString str){
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("jfSetValue('ShanbayDict_word_definition',\"%1\");").arg(str));

}
void DictView::setWordExample(QString str){
    //qDebug()<<"examples"<<str;
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("jfSetValue('ShanbayDict_word_example',\"%1\");").arg(str));
}
void DictView::setTipInfo(QString str){
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("jfSetValue('ShanbayDict_info',\"%1\");").arg(str));
}
void DictView::showSpeak(int show){
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("lgShowElement('ShanbayDict_speak',\"%1\");").arg(show));
}
void DictView::showShanbay(int show){
    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("lgShowElement('ShanbayDict',\"%1\");").arg(show));
}


