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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "dictview.h"
#include "texttranslatenet.h"
#include <QRegExp>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void signalLoginClose();
protected:
        void closeEvent(QCloseEvent *event);
        void keyPressEvent(QKeyEvent *event);
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void queryWordClick();
    void addWordClick();
    void playClick();
    void menuClick();
    void about();
    void help();
    void backwardClick();
    void frontwardClick();
    void tabCurrentChanged(int index);
    void addExampleClick();
    void addExampleFinished(const QString &msg);
    //void seadictQueryFinished(QString& resulthtml);
    void query(QString text);
    void speakWord(QString mp3);
    void swapClick();
    void translateClick();
    void translateFinshed(QString dSentence);
    void wikiLoadFinshed(bool ok);
    void wikiUrlChange(const QUrl &url);
private:
    Ui::MainWindow *ui;
    TextTranslateNet textTranslateNet;

public:
    DictView *dictView;
    void setHistoryStatus();
    QRegExp exp;
};


#endif // MAINWINDOW_H
