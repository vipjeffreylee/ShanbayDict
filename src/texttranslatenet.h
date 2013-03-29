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
#ifndef TEXTTRANSLATENET_H
#define TEXTTRANSLATENET_H

#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
class TextTranslateNet : public QObject
{
    Q_OBJECT
public:
    explicit TextTranslateNet(QObject *parent = 0);
    ~TextTranslateNet();
signals:
    void translateFinshed(QString);
public slots:
    void httpfinished(QNetworkReply*);
public:
    void translate(QString sSentence);
private:
    QNetworkAccessManager * http;

    
};

#endif // TEXTTRANSLATENET_H
