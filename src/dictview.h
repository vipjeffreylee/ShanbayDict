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
#ifndef DICTVIEW_H
#define DICTVIEW_H
#include <QFrame>
#include <QUrl>
namespace Ui {
class DictView;
}
class DictView : public QFrame
{
    Q_OBJECT
    
public:
    explicit DictView(QWidget *parent = 0);
    ~DictView();
    
private:
    Ui::DictView *ui;
signals:
    void speakClick();
    void addwordClick();
    void speakWord(QString wordmp3);
    void queryWord(QString word);
private slots:
    void linkClicked(const QUrl & url);


public:
    void showShanbay(int show);
    void showSeadict(int show);
    void clear();
    void setShanbayNetStatus(int status);
    void setSeadictNetStatus(int status);
    void setWordNamePron(QString str);
    void setWordDefinition(QString str);
    void setWordExample(QString str);
    void setTipInfo(QString str);
    void showSpeak(int show);
    void setSeaDict(QString& str);
};

#endif // DICTVIEW_H
