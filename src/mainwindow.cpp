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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QDesktopWidget>
#include "dict.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QFile>
#include <QCursor>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QWebPage>
#include <QWebFrame>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int x=(qApp->desktop()->width() - this->width())/2;
    int y=(qApp->desktop()->height() - this->height())/2;
    // this->setGeometry (x,y,this->width(),this->height());
    this->move (x,y);
    exp.setPattern("[a-zA-Z]");
    connect(ui->queryButton,SIGNAL(clicked()),this,SLOT(queryWordClick()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(queryWordClick()));
    connect(ui->backward,SIGNAL(Clicked()),this,SLOT(backwardClick()));
    connect(ui->frontward,SIGNAL(Clicked()),this,SLOT(frontwardClick()));
    //connect(qApp->clipboard(),SIGNAL(dataChanged()),this,SLOT(clipboardQuery()));

    //qDebug()<<qApp->clipboard()->supportsSelection()<<"supportsSelection";

    //connect(DICT::shanbayNet,SIGNAL(signalAddwordFinished(bool)),this,SLOT(addWordFinshed(bool)));
    connect(ui->menuButton,SIGNAL(clicked()),this,SLOT(menuClick()));
    //QPixmap p(":/pic/logo.png");
    //p.save("d:/app.ico");
    //ui->pushButton->setIcon(p.copy(32,64,32,32));
    //ui->pushButton->setIconSize(QSize(32,32));
    //ui->playButton->setText("");
    //ui->playButton->setIconSize(QSize(32,32));
    //p.copy(32,6,48,48).save("d:/sound1.png");
    // ui->playButton->setIcon(QIcon(":/pic/sound1.png"));
    //ui->playButton->setIcon(QIcon(":/pic/logo.png"));
    //ui->playButton->setStyleSheet("QPushButton:hover{border-image:url(:/pic/sound2.png)}");
    // ui->playButton->setCursor(Qt::OpenHandCursor);
    dictView=new DictView(this);
    connect(dictView,SIGNAL(speakClick()),this,SLOT(playClick()));
    connect(dictView,SIGNAL(addwordClick()),this,SLOT(addWordClick()));
    connect(dictView,SIGNAL(queryWord(QString)),this,SLOT(query(QString)));
    connect(dictView,SIGNAL(speakWord(QString)),this,SLOT(speakWord(QString)));
    ui->centralwidget->setLayout(ui->mainLayout);
    ui->tab0verticalLayout->addWidget(dictView);
    ui->tab0->setLayout(ui->tab0verticalLayout);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabCurrentChanged(int)));
    ui->tab1->setLayout(ui->tab1verticalLayout);
    connect(ui->addExampleButton,SIGNAL(clicked()),this,SLOT(addExampleClick()));
    connect(DICT::shanbayNet,SIGNAL(signalAddExampleFinished(const QString&)),this,SLOT(addExampleFinished(const QString&)));
    ui->tab2->setLayout(ui->tab2VerticalLayout);
    connect(ui->swapButton,SIGNAL(clicked()),this,SLOT(swapClick()));
    connect(ui->translateButton,SIGNAL(clicked()),this,SLOT(translateClick()));
    connect(&textTranslateNet,SIGNAL(translateFinshed(QString)),this,SLOT(translateFinshed(QString)));

    ui->tab3->setLayout(ui->tab3VerticalLayout);
    connect(ui->wikiWebView,SIGNAL(loadFinished(bool)),this,SLOT(wikiLoadFinshed(bool)));
    connect(ui->wikiWebView,SIGNAL(urlChanged(QUrl)),this,SLOT(wikiUrlChange(QUrl)));
    connect(ui->wikiWebView,SIGNAL(loadStarted()),ui->progressBar,SLOT(reset()));
    connect(ui->wikiWebView,SIGNAL(loadProgress(int)),ui->progressBar,SLOT(setValue(int)));
    ui->tab4->setLayout(ui->tab4VerticalLayout);

    ui->shanbayWebView->page()->networkAccessManager()->setCookieJar(DICT::shanbayNet->http->cookieJar());
}

MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow close这个析构函数不执行啊";
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug()<<"MainWindow coseEventcoseEventcoseEventcoseEventcoseEvent!";
   if (DICT::trayIcon->isVisible()) {
    //        QMessageBox::information(this, tr("Systray"), tr("The program will keep running in the "
    //			"system tray. To terminate the program, "
    //			"choose <b>Quit</b> in the context menu "
    //			"of the system tray entry."));

    hide();
    event->ignore();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    //qDebug()<<"key press:"<<e->key()<<e->modifiers();
    if(e->modifiers()==Qt::AltModifier){
        //if(ui->lineEdit->isActiveWindow()) return;
        this->setFocus();
    }
    if(e->modifiers()==Qt::AltModifier&&e->key()==Qt::Key_D){
        ui->lineEdit->selectAll();
        ui->lineEdit->setFocus();
        return;
    }
}


void MainWindow::menuClick(){
    DICT::dictMenu->popup(QCursor::pos());
}
void MainWindow::query(QString text){
    ui->lineEdit->setText(text);
    queryWordClick();
}
void MainWindow::speakWord(QString mp3){
    DICT::speak(mp3);
}

void MainWindow::queryWordClick(){
    QString querystr=ui->lineEdit->text().trimmed();
    if(querystr.isEmpty()) return;
    if(ui->tabWidget->currentIndex()!=3){
        ui->tabWidget->setCurrentIndex(0);
        DICT::forMainWinQuery(querystr);
        ui->lineEdit->selectAll();
    }else{
        ui->tabWidget->setCursor(Qt::BusyCursor);
        ui->wikiWebView->hide();
        ui->wikiWebView->stop();
        qDebug()<<"exp.indexIn(querystr)"<<exp.indexIn(querystr);
        QString strUrl;
        if(exp.indexIn(querystr)==-1){
            strUrl=QString("http://zh.wikipedia.org/wiki/%1").arg(querystr);
        }else{
            strUrl=QString("http://en.wikipedia.org/wiki/%1").arg(querystr);
        }
        qDebug()<<"zh.wikipedia.org "+strUrl;
        ui->wikiWebView->load(QUrl(strUrl));

    }
}
void MainWindow::setHistoryStatus(){
    ui->backward->setEnabled(DICT::history.canBackward());
    ui->frontward->setEnabled(DICT::history.canForward());
    ui->backward->setToolTip(DICT::history.getTooltip());
    ui->frontward->setToolTip(DICT::history.getTooltip());
}

void MainWindow::backwardClick(){
    DICT::flipPage(DICT::BACK);
    ui->lineEdit->setText(DICT::word->name);
    setHistoryStatus();
}
void MainWindow::frontwardClick(){
    DICT::flipPage(DICT::FRONT);
    ui->lineEdit->setText(DICT::word->name);
    setHistoryStatus();
}

void MainWindow::addWordClick(){
    DICT::addWord();
}


void MainWindow::playClick(){
    if(DICT::word->audioOk()){
        dictView->setTipInfo("");
        DICT::speak(DICT::word);
    }else{
        dictView->setTipInfo("该单词没有声音文件");
    }

}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (this->isVisible()) {
            if (this->isMinimized()) {
                this->showNormal();
                this->raise();
                this->activateWindow();
                ui->lineEdit->setFocus();
                ui->lineEdit->selectAll();
            } else {
                this->hide();
            }

        } else {
            this->show();
            this->raise();
            this->activateWindow();
            ui->lineEdit->setFocus();
            ui->lineEdit->selectAll();
        }
        break;
    case QSystemTrayIcon::MiddleClick:

        break;
    default:
        ;
    }
}
void MainWindow::tabCurrentChanged(int index){
    qDebug()<<"tab index"<<index;
    if(index==2){
        ui->statusbar->showMessage("自动识别源语言，源语言识别为中文，则翻译方向为“中 -> 英” 源语言识别为英文，则翻译方向为“英 -> 中”");
        if(!ui->lineEdit->text().isEmpty()){
            ui->sourceTextEdit->setPlainText(ui->lineEdit->text());
            this->translateClick();
        }
    }else{
        if(index==4){
            if(!ui->shanbayWebView->url().toString().contains("http")){
                ui->shanbayWebView->load(QUrl("http://www.shanbay.com"));
            }


        }else{
            //ui->shanbayWebView->load(QUrl("http://www.sohu.com"));
           ui->statusbar->showMessage("扇贝词典，扇贝网背单词最好的桌面工具。");
        }

    }
}
void MainWindow::addExampleClick(){
    DICT::shanbayNet->addExample(ui->exampleText->toPlainText(),ui->translationText->toPlainText());
}
void MainWindow::addExampleFinished(const QString &msg){
    ui->addexampleinfo->setText(msg);
}
void MainWindow::swapClick(){
    QString tmp=ui->sLanguage->text();
    ui->sLanguage->setText(ui->dLanguage->text());
    ui->dLanguage->setText(tmp);
}
void MainWindow::translateClick(){
    //ui->statusbar->showMessage("正在为你给力翻译中，请耐心等待！如果长时间没有返回结果，请再次点击翻译按钮尝试..........",3000);
    //ui->destBrowser->setHtml("正在为你给力翻译中，请耐心等待！如果长时间没有返回结果，请再次点击翻译按钮尝试..........");
    textTranslateNet.translate(ui->sourceTextEdit->toPlainText());
}
void MainWindow::translateFinshed(QString dSentence){
    if(dSentence.isEmpty()){
        ui->destBrowser->setHtml("哇塞！没得到翻译结果，请再次点击翻译按钮尝试！");
    }else{
        ui->destBrowser->setHtml(dSentence);
    }

}
void MainWindow::wikiLoadFinshed(bool ok){
    qDebug()<<"wikiLoadFinshed "<<ok;
    if(ok){
        ui->wikiWebView->page()->mainFrame()->evaluateJavaScript("var e=document.getElementById('mw-panel');if(e) e.style.display='none';"
                                                                 "e=document.getElementById('mw-head');if(e) e.style.display='none';"
                                                                 "e=document.getElementById('mw-page-base');if(e) e.style.display='none';"
                                                                 "e=document.getElementById('mw-head-base');if(e) e.style.display='none';"
                                                                 "e=document.getElementById('content');if(e) e.style.marginLeft ='0em';"
                                                                 "var f=document.getElementsByClassName('mw-content-ltr')[0];"
                                                                 "if(e) if(f) {e.innerHTML=f.innerHTML;document.getElementsByClassName('infobox sisterproject')[0].style.display='none';};"
                                                                 "var edits=document.getElementsByClassName('editsection');for(var i=0;i<edits.length;i++){edits[i].style.display='none';};"
                                                                 "e=document.getElementById('footer');if(e) e.style.display='none';"
                                                                 "e=document.getElementById('mw-articlefeedback');if(e) e.style.display='none';"
                                                                 );

    }else{
        ui->wikiWebView->setHtml("<b>Not to the Great Wall non-real man</b>");
    }
    ui->wikiWebView->show();
    ui->progressBar->hide();
    ui->tabWidget->setCursor(Qt::ArrowCursor);
}
void MainWindow::wikiUrlChange(const QUrl &url){
    ui->wikiWebView->hide();
    ui->progressBar->show();
    ui->statusbar->showMessage(url.toString());
    ui->tabWidget->setCursor(Qt::BusyCursor);
}

void MainWindow::help(){
    qDebug("open doc");
    if(QFile::exists("help.doc")){
        QDesktopServices::openUrl(QUrl::fromLocalFile("help.doc"));
    }else{
        QMessageBox::information(this, tr("%1帮助").arg(DICT::versioninformation), tr("感谢使用扇贝词典！<br> "
                                                                                    "屏幕取词使用方法：鼠标双击单词或者按住鼠标左键选中单词<br>"
                                                                                    "屏幕鼠标取词只有在菜单中选中鼠标取词才生效。<br>"
                                                                                    "主窗口快捷键：Alt+D查词录入框获得焦点<br>%1"
                                                                                   ).arg(DICT::licenceinformation));
    }

}

void MainWindow::about(){
    QMessageBox::about(this, tr("关于%1").arg(DICT::versioninformation), DICT::licenceinformation);
}
