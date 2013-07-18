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
#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QVariantMap>

class Config
{
public:
    Config();
    ~Config();
private:
    /*
    QString username;
    QString userpass;
    bool savepass;
    bool autologin;
    bool autospeak;
    bool autoaddword;
    bool getscreentext;
    bool getclipboardtext;
    bool getselectedtext;
    bool showquerylogo;
    bool autorun;
    bool autohide;
    */

    QSettings *settings;
    void load();

    QVariantMap _config;
public:
    void save();
    QString getUsername() const;
    void setUsername(const QString &name);
    QString getUserpass() const;
    void setUserpass(const QString &text);
    bool isSavepass() const;
    void setSavepass(bool value);
    bool isAutologin() const;
    void setAutologin(bool value);
    bool isAutospeak() const;
    void setAutospeak(bool value);
    bool isGetscreentext() const;
    void setScreentext(bool value);
    bool isGetclipboardtext() const;
    void setClipboardtext(bool value);
    bool isGetselectedtext() const;
    void setSelectedtext(bool value);
    bool isShowquerylogo() const;
    void setShowquerylogo(bool value);
    bool isAutorun() const;
    void setAutorun(bool value);
    bool isAutohide() const;
    void setAutohide(bool value);
    bool isAutoaddword() const;
    void setAutoaddword(bool value);
};

#endif // CONFIG_H
