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
#ifndef HISTORY_H
#define HISTORY_H
#include <QList>
#include <QStringList>
#include <QMap>
#include "englishword.h"
class History
{
public:
    History();
private:
    QString today;
    QList<EnglishWord> todayWordList;
    int pos;
    QStringList queryDate;
    QMap<QString,QList<EnglishWord> > queryMap;
public:
    inline bool canBackward(){
        return pos>0;
    }
    inline bool canForward(){
        return pos<todayWordList.length()-1;
    }
    inline bool addWord(EnglishWord word){
        if(!todayWordList.contains(word)){
            todayWordList<<EnglishWord(word);
            pos=todayWordList.length()-1;
            return true;
        }
        return false;
    }
    inline EnglishWord backward(){
        if(pos>0) pos--;
        return todayWordList.at(pos);
    }
    inline EnglishWord forward(){
        if(pos<todayWordList.length()-1) pos++;
            return todayWordList.at(pos);
    }
    inline QString getTooltip(){
        return QString("当前显示第%1个，今日共查询%2个").arg(pos+1).arg(todayWordList.length());
    }
};

#endif // HISTORY_H
