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
#include "ballonwindow.h"
#include "ui_ballonwindow.h"
#include "dict.h"
#include <QMovie>
#include <QDesktopWidget>
#include <QClipboard>

BallonWindow::BallonWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallonWindow)
{
    ui->setupUi(this);
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(autohide()));
    //connect(DICT::shanbayNet,SIGNAL(signalAddwordFinished(bool)),this,SLOT(addWordFinshed(bool)));
    //QPixmap p(":/pic/icons.png");
    //ui->pushButton->setIcon(p.copy(32,64,32,32));
    //ui->pushButton->setIconSize(QSize(32,32));
    //ui->playButton->setIconSize(QSize(32,32));
    //p.copy(32,6,48,48).save("d:/sound1.png");
    // ui->playButton->setIcon(QIcon(":/pic/sound1.png"));
    //ui->playButton->setIcon(QIcon(":/pic/logo.png"));
    // ui->addwordButton->setStyleSheet("QPushButton{border-image:url(:/img/speak0.png);}QPushButton:hover{border-image:url(:/img/speak1.png);}");
    // ui->playButton->setCursor(Qt::OpenHandCursor);
    // this->setLayout(ui->mainLayout);

    logo=new ClickLabel();
#ifdef Q_OS_WIN
   //  this->setWindowFlags(Qt::Popup);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    logo->setWindowFlags(Qt::Popup);
#else
    logo->setWindowFlags(Qt::FramelessWindowHint|Qt::ToolTip);
#endif

    connect(logo,SIGNAL(Clicked()),this,SLOT(logoClick()));
    //    QMovie *movie=new QMovie(":/pic/loading.gif");
    //    logo->setMovie(movie);
    //    movie->start();
    logo->setGeometry(0,0,32,32);
    logo->setPixmap(QPixmap(":/img/logo.png").scaled(QSize(32,32), Qt::IgnoreAspectRatio));
    dictView=new DictView(this);
    connect(dictView,SIGNAL(speakClick()),this,SLOT(playClick()));
    connect(dictView,SIGNAL(addwordClick()),this,SLOT(addWordClick()));
    connect(dictView,SIGNAL(queryWord(QString)),this,SLOT(query(QString)));
    connect(dictView,SIGNAL(speakWord(QString)),this,SLOT(speakWord(QString)));
    this->setLayout(ui->mainLayout);
    ui->mainLayout->addWidget(dictView);

}

BallonWindow::~BallonWindow()
{
    delete ui;
}
bool  BallonWindow::event ( QEvent * event )
{
    if (event->type() == QEvent::ActivationChange)
    {
        if(QApplication::activeWindow() != this)
        {
            this->hide();
        }
    }
    return QWidget::event(event);
}
void BallonWindow::addWordClick(){
    DICT::addWord();
}

void BallonWindow::clipboardQuery(){
    query(qApp->clipboard()->text());
}
void BallonWindow::logoClick(){
    qDebug()<<"logoClick"<<endl;
    logo->hide();
    dictView->setTipInfo("");
    query(queryText);
}
void BallonWindow::query(QString text){
    qDebug()<<"BallonWindow::query:"<<text;
    showBallon();
    queryText=text;
    DICT::forBallonWinQuery(queryText);
}
void BallonWindow::speakWord(QString mp3){
    DICT::speak(mp3);
}

void BallonWindow::showBallon(){
    qDebug()<<"BallonWindow::showBallon()";
    if(this->isVisible()) return;
    QPoint point;
    if(DICT::cfg->isShowquerylogo()){
        point=logo->pos()+QPoint(36,50);
    }else{
        point=QCursor::pos()+QPoint(10,15);
    }
    qDebug()<<point;
    if((point.x()+this->width())>qApp->desktop()->width()){
        point.setX(qApp->desktop()->width()-this->width()-100);
    }
    if((point.y()+this->height())>qApp->desktop()->height()){
        point.setY(point.y()-this->height()-50);
    }
    this->move(point);
    this->show();
    this->activateWindow();
    this->focusWidget();

}
void BallonWindow::showQueryLogo(QString text){
    qDebug()<<"showQueryLogoshowQueryLogoshowQueryLogoshowQueryLogoshowQueryLogoshowQueryLogoshowQueryLogo";
    if(this->isVisible()){
        this->query(text);//本窗口取词
    }else{
        logo->hide();
        timer->stop();
        logo->setWindowOpacity(qreal(0.9));
        logo->move(QCursor::pos()-QPoint(36,46));
        // logo->setText("ddddddddddddddddddddddddddddddddddd");
        logo->show();
        timercount=0.9;
        timer->start(500);
        queryText=text;
    }
}
void BallonWindow::playClick(){
    DICT::speak(DICT::word);
}
void BallonWindow::autohide(){
    //qDebug()<<"autohide"<<this->underMouse()<<this->hasFocus()<<timercount<<this->isActiveWindow();
    if(!logo->rect().contains(logo->mapFromGlobal(QCursor::pos()))){
        logo->setWindowOpacity(timercount);
        if(timercount<0){
            timer->stop();
            logo->hide();
        }
        timercount-=0.1;
        mousein=false;

    }else{
        if(!mousein){
            mousein=true;
            timercount=0.9;
            logo->setWindowOpacity(qreal(0.9));
        }
    }

}

void BallonWindow::closeEvent(QCloseEvent *event) {
    qDebug()<<"BallonWindow coseEventcoseEventcoseEventcoseEventcoseEvent!";
    if (DICT::trayIcon->isVisible()) {
        event->ignore();
        this->hide();
    }else{
        logo->close();
        logo->deleteLater();
    }
}


bool BallonWindow::isworking(){
    return logo->isVisible()||this->isVisible();
}
