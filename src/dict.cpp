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
#include "dict.h"
#ifdef Q_OS_WIN
#include "winhook.h"
#endif
#include <QMediaPlayer>
#include <QMessageBox>
#include <QDate>
#include "dictview.h"
#include "cfgdialog.h"
#include <QClipboard>
#include <QDir>
namespace DICT{
Msg *msg;
Config *cfg;

DictView *dictView;
ShanbayNet *shanbayNet;
YoudaoNet *youdaoNet;
MainWindow *mainWindow=0;
BallonWindow *ballonWindow;
LoginDialog *loginDialog;
CfgDialog *cfgDialog;
QSystemTrayIcon *trayIcon;
EnglishWord *word;
QMenu *dictMenu ;
QAction *getscreenwordAction;
QAction *cfgAction;
QAction *autospeakAction;
QAction *quitAction;
QAction *aboutAction;
QAction *helpAction;
QMediaPlayer *player;
History history;

QString licenceinformation;
QString versioninformation;

void speak(EnglishWord* w){
    if(!w->audioOk()) return;
    speak(w->audio);
}
void speak(QString mp3){
    qDebug()<<mp3;
    mp3=mp3.replace("sounds","audio/us");

    player->setMedia(QUrl(mp3));
    player->play();
    qDebug()<<mp3;
}

Msg::Msg(){
}
Msg::~Msg(){
}
void Msg::quit(){
    close();
}
void Msg::slotYoudaoQueryFinished(){
    dictView->setYoudaoNetStatus(1);
    dictView->setYoudaoWord(DICT::word->youdaoWord);
}

void Msg::slotShanbayQueryFinished(){
    dictView->setShanbayNetStatus(1);//ok
    if(DICT::word->name.isEmpty()){
        dictView->setTipInfo(tr("扇贝网服务器没有返回%1的释义，请使用文本翻译功能试试。").arg(DICT::shanbayNet->queryword));
        return;
    }
    dictView->setWordNamePron(DICT::word->formatNameAndPron());
    dictView->setWordDefinition(DICT::word->formatDefinition());
    if(DICT::cfg->isAutospeak()){
        DICT::speak(DICT::word);
    }
    if(DICT::history.addWord(*DICT::word)){
        mainWindow->setHistoryStatus();
    }
    if(DICT::cfg->isAutoaddword()){
        DICT::addWord();
        qDebug()<<"auto add word";
    }

}
void Msg::slotShanbayQueryExampleFinished(){
    dictView->setWordExample(DICT::word->formatExamples());
}
void Msg::getscreenwordActionClick(){
    cfg->setScreentext(getscreenwordAction->isChecked());
    DICT::setScreenText();
}
void Msg::cfgActionClick(){
    //cfg->setAutologin(autologinAction->isChecked());
    cfgDialog->loadcfg();
    cfgDialog->show();
}
void Msg::autospeakActionClick(){
    cfg->setAutospeak(autospeakAction->isChecked());
}
void Msg::slotClipboardDataChanged(){
    qDebug()<<"粘贴板"<<qApp->clipboard()->text();

    if(!DICT::ballonWindow->isworking()){
#ifdef Q_OS_WIN
        if(!WINHOOK::isGetingword()) DICT::querySelectedText(qApp->clipboard()->text());
#else
        DICT::querySelectedText(qApp->clipboard()->text());
#endif
    }
}
void Msg::slotClipboardSelectionChanged(){
#ifndef Q_OS_WIN
    qDebug()<<"粘贴板选取内容"<<qApp->clipboard()->text(QClipboard::Selection);
    if(!DICT::ballonWindow->isworking()){
        DICT::querySelectedText(qApp->clipboard()->text(QClipboard::Selection));
    }

#endif
}
void Msg::slotAddwordFinished(bool ok){
    if(ok){
        dictView->setTipInfo("添加单词成功");
    }else{
        dictView->setTipInfo("添加单词失败");
    }
}
void setScreenText(){
    if(cfg->isGetscreentext()){
        if(cfg->isGetselectedtext()){
#ifdef Q_OS_WIN
            WINHOOK::setHook();
            WINHOOK::setHook();//有时候一次不成功，微软的api真是莫名奇妙，鄙视
#else
            QObject::connect(qApp->clipboard(),SIGNAL(selectionChanged()),msg,SLOT(slotClipboardSelectionChanged()));
#endif
        }else{
#ifdef Q_OS_WIN
            WINHOOK::unHook();
            WINHOOK::unHook();//有时候一次不成功，微软的api真是莫名奇妙，鄙视
#else
            QObject::disconnect(qApp->clipboard(),SIGNAL(selectionChanged()),msg,SLOT(slotClipboardSelectionChanged()));
#endif

        }
        if(cfg->isGetclipboardtext())   {
            QObject::connect(qApp->clipboard(),SIGNAL(dataChanged()),msg,SLOT(slotClipboardDataChanged()));
        }else{
             QObject::disconnect(qApp->clipboard(),SIGNAL(dataChanged()),msg,SLOT(slotClipboardDataChanged()));
        }
    }else{
#ifdef Q_OS_WIN
        WINHOOK::unHook();
        WINHOOK::unHook();
#endif
        QObject::disconnect(qApp->clipboard(),0,0,0);
    }
}

void addWord(){
    if(DICT::word->learning_id=="0"){
        dictView->setTipInfo("");
        DICT::shanbayNet->addWord();
    }else{
        dictView->setTipInfo("你之前添加过这个单词");
    }
}

void updateCfg(){
    getscreenwordAction->setChecked(cfg->isGetscreentext());
    autospeakAction->setChecked(cfg->isAutospeak());
    setScreenText();
}

void querySelectedText(QString text){
    text=text.trimmed();
    if(text.isEmpty()||text.length()>20){
        return;
    }
    if(cfg->isShowquerylogo()){
        ballonWindow->showQueryLogo(text);
    }else{
        ballonWindow->query(text);
    }

}
void forlicence(){
    if(QDate::currentDate()>=QDate(2013,12,21)){
        QMessageBox::warning(mainWindow, QObject::tr("扇贝词典需要更新了"),QObject::tr("为了更好的为大家服务，请下载安装最新版本扇贝词典。<br>%1").arg(licenceinformation));
        close();
    }
}
void query(QString &word){
    dictView->clear();
    dictView->setShanbayNetStatus(0);//loading
    dictView->setYoudaoNetStatus(0);
    shanbayNet->queryWord(word);
    youdaoNet->queryWord(word);
}

void forBallonWinQuery(QString word){
    dictView=ballonWindow->dictView;
    query(word);
}

void forMainWinQuery(QString word){
    forlicence();
    dictView=mainWindow->dictView;
    query(word);
}

void flipPage(BACKFRONT bf){
    dictView=mainWindow->dictView;
    dictView->clear();
    if(bf==BACK){
        *DICT::word=DICT::history.backward();
        msg->slotShanbayQueryFinished();
    }else{
        *DICT::word=DICT::history.forward();
        msg->slotShanbayQueryFinished();
    }
}

void close(){
    //qDebug()<<autologinAction->isChecked();
#ifdef Q_OS_WIN
    WINHOOK::unHook();
#endif
    player->deleteLater();
    cfg->save();
    trayIcon->hide();
    trayIcon->deleteLater();
    delete cfg;
    // delete loginWindow;
    // loginWindow->deleteLater();
    shanbayNet->deleteLater();

    //delete trayIcon;
    delete word;
    dictMenu->deleteLater();
    cfgDialog->close();
    cfgDialog->deleteLater();
    mainWindow->close();
    mainWindow->deleteLater();
    ballonWindow->close();
    ballonWindow->deleteLater();
    msg->deleteLater();
    //qApp->closeAllWindows();
    //qApp->quit();
}
void loginFinshed(bool ok){
    if(ok){
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        player = new QMediaPlayer;
        youdaoNet=new YoudaoNet();
        QObject::connect(youdaoNet,SIGNAL(signalQueryFinished()),msg,SLOT(slotYoudaoQueryFinished()));
        QObject::connect(shanbayNet,SIGNAL(signalQueryFinished()),msg,SLOT(slotShanbayQueryFinished()));
        QObject::connect(shanbayNet,SIGNAL(signalQueryExampleFinished()),msg,SLOT(slotShanbayQueryExampleFinished()));
        QObject::connect(shanbayNet,SIGNAL(signalAddwordFinished(bool)),msg,SLOT(slotAddwordFinished(bool)));
        mainWindow=new MainWindow();
        ballonWindow=new BallonWindow();
        // ballonWindow->setWindowFlags(Qt::Popup);
        cfgDialog=new CfgDialog();
        dictMenu  = new QMenu("菜单",QApplication::desktop());
        //dictMenu->setLayoutDirection(Qt::LeftToRight);
        helpAction =new QAction(QObject::tr("帮助"),mainWindow);
        helpAction->setIcon(QIcon(":/img/help.png"));
        quitAction = new QAction(QObject::tr("退出程序"), mainWindow);
        cfgAction=new QAction(QObject::tr("软件设置"),mainWindow);
        autospeakAction=new QAction(QObject::tr("自动发音"),mainWindow);
        getscreenwordAction=new QAction(QObject::tr("屏幕取词"),mainWindow);
        aboutAction=new QAction(QObject::tr("关于"),mainWindow);
        aboutAction->setIcon(QIcon(":/img/about.png"));
        autospeakAction->setCheckable(true);
        getscreenwordAction->setCheckable(true);
        autospeakAction->setChecked(cfg->isAutospeak());
        getscreenwordAction->setChecked(cfg->isGetscreentext());
        quitAction->setIcon(QIcon(":/img/quit.png"));

        dictMenu->addAction(helpAction);
        dictMenu ->addAction(getscreenwordAction);
        dictMenu ->addAction(autospeakAction);
        dictMenu ->addAction(cfgAction);
        dictMenu->addAction(aboutAction);
        dictMenu ->addSeparator();
        dictMenu ->addAction(quitAction);
        QObject::connect(getscreenwordAction,SIGNAL(triggered()),msg,SLOT(getscreenwordActionClick()));
        QObject::connect(autospeakAction,SIGNAL(triggered()),msg,SLOT(autospeakActionClick()));
        QObject::connect(cfgAction,SIGNAL(triggered()),msg,SLOT(cfgActionClick()));
        QObject::connect(quitAction, SIGNAL(triggered()),msg, SLOT(quit()));
        QObject::connect(aboutAction,SIGNAL(triggered()),mainWindow,SLOT(about()));
        QObject::connect(helpAction,SIGNAL(triggered()),mainWindow,SLOT(help()));
        word=new EnglishWord();
        if(trayIcon==0){
            trayIcon = new QSystemTrayIcon(mainWindow);
            QIcon icon = QIcon(":/img/logo.png");
            trayIcon->setContextMenu(dictMenu );
            trayIcon->setIcon(icon);
        }

        //trayIcon->setToolTip(tr(""));
        QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), mainWindow, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
        //mainWindow->login();
        //mainWindow->show();
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        setScreenText();//设置屏幕取词
        QString title=QObject::tr("%1-%2-%3").arg(DICT::versioninformation).arg(DICT::shanbayNet->username).arg(DICT::shanbayNet->nickname);
        mainWindow->setWindowTitle(title);
        trayIcon->setToolTip(title);
        trayIcon->show();
        if(!(cfg->isAutorun()||cfg->isAutohide())){
            mainWindow->show();
        }
        loginDialog->deleteLater();
        //qApp->setQuitOnLastWindowClosed(false);
        //moo=new Phonon::MediaObject;
        // Phonon::AudioOutput *device=new Phonon::AudioOutput;
        // Phonon::createPath(moo,device);
    }else{
        delete msg;
        delete cfg;
        delete shanbayNet;
        loginDialog->deleteLater();
    }


}
void relogin(){
    if(mainWindow!=0){
        delete msg;
        delete cfg;
        delete mainWindow;
        delete ballonWindow;
        delete cfgDialog;
        delete shanbayNet;
        //delete seadictNet;
        //delete trayIcon;
        delete word;
        delete dictMenu;
    }
    login();
}

void login(){

#ifdef NDEBUG
  //  QDir::setCurrent(qApp->applicationDirPath());
   qDebug()<<"release";
#endif
    msg=new Msg();
    cfg=new Config();
    shanbayNet=new ShanbayNet();
    loginDialog=new LoginDialog();
    loginDialog->show();
}
}
