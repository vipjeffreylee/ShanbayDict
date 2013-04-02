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
#ifndef DICT_H
#define DICT_H
#include <QSystemTrayIcon>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDesktopWidget>
#include <QApplication>
#include <QAction>
#include "shanbaynet.h"
#include "youdaonet.h"
#include "englishword.h"
#include "mainwindow.h"
#include "ballonwindow.h"
#include "logindialog.h"
#include "config.h"
#include "history.h"
//class ShanbayNet;
//class SeadictNet;
//class EnglishWord;
//class MainWindow;
//class BallonWindow;
//class Config;
//class History;
namespace DICT{
class Msg:public QObject{
Q_OBJECT
public:
    Msg();
    ~Msg();
private:
    void setScreenText();
signals:
    //void signalMainQueryFinished();
    //void signalBallonQueryFinished();
public slots:
    void slotShanbayQueryFinished();
    void slotYoudaoQueryFinished();
    void slotShanbayQueryExampleFinished();
    void slotAddwordFinished(bool ok);
    void quit();
    void getscreenwordActionClick();
    void autospeakActionClick();
    void cfgActionClick();
    void slotClipboardDataChanged();
    void slotClipboardSelectionChanged();
};
enum BACKFRONT{BACK,FRONT};
extern Msg *msg;
extern Config *cfg;
extern ShanbayNet *shanbayNet;
extern YoudaoNet *youdaoNet;
extern MainWindow *mainWindow;
extern BallonWindow *ballonWindow;
extern LoginDialog * loginDialog;
extern QSystemTrayIcon *trayIcon;
extern EnglishWord *word;
extern QSettings *settings;
extern QMenu *dictMenu ;
extern void login();
extern void relogin();
extern void loginFinshed(bool ok);
extern void close();
extern void forBallonWinQuery(QString word);
extern void querySelectedText(QString text);
extern void forMainWinQuery(QString word);
extern History history;
extern void speak(EnglishWord* w);
extern void speak(QString mp3);
extern QString licenceinformation;
extern QString versioninformation;
extern void flipPage(BACKFRONT);
extern void updateCfg();
extern void addWord();
extern void setScreenText();
}

#endif // DICT_H
