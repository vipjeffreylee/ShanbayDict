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
#include "config.h"

Config::Config()
{
    settings=new QSettings("shanbay.ini",QSettings::IniFormat);
    load();
}
Config::~Config(){
    settings->sync();
    settings->deleteLater();
}

void Config::load(){
    username=settings->value("username","").toString();
    userpass=settings->value("userpass","").toString();
    savepass=settings->value("savepass",false).toBool();
    autologin=settings->value("autologin",false).toBool();
    autospeak=settings->value("autospeak",true).toBool();
    getscreentext=settings->value("getscreentext",true).toBool();
#ifdef Q_OS_WIN
    getclipboardtext=settings->value("getclipboardtext",true).toBool();
    getselectedtext=settings->value("getselectedtext",false).toBool();
#else
    getclipboardtext=settings->value("getclipboardtext",false).toBool();
    getselectedtext=settings->value("getselectedtext",true).toBool();
#endif
    showquerylogo=settings->value("showquerylogo",true).toBool();
    autorun=settings->value("autorun",false).toBool();
    autohide=settings->value("autohide",true).toBool();
    autoaddword=settings->value("autoaddword",false).toBool();
}
void Config::save(){
    settings->setValue("username",username);
    settings->setValue("userpass",userpass);
    settings->setValue("savepass",savepass);
    settings->setValue("autologin",autologin);
    settings->setValue("autospeak",autospeak);
    settings->setValue("getscreentext",getscreentext);
    settings->setValue("getclipboardtext",getclipboardtext);
    settings->setValue("getselectedtext",getselectedtext);
    settings->setValue("showquerylogo",showquerylogo);
    settings->setValue("autorun",autorun);
    settings->setValue("autohide",autohide);
    settings->setValue("autoaddword",autoaddword);
    settings->sync();

}
QString Config::getUsername(){
    return username;
}
void Config::setUsername(QString name){
    username=name;
}

QString Config::getUserpass(){
    return userpass;
}
void Config::setUserpass(QString text){
    userpass=text;
}

bool Config::isSavepass(){
    return savepass;
}
void Config::setSavepass(bool value){
    savepass=value;
}

bool Config::isAutologin(){
    return autologin;
}
void Config::setAutologin(bool value){
    autologin=value;
}

bool Config::isAutohide(){
    return autohide;
}
void Config::setAutohide(bool value){
    autohide=value;
}

bool Config::isAutospeak(){
    return autospeak;
}
void Config::setAutospeak(bool value){
    autospeak=value;
}

bool Config::isAutorun(){
    return autorun;
}
void Config::setAutorun(bool value){
    autorun=value;
}

bool Config::isGetclipboardtext(){
    return getclipboardtext;
}
void Config::setClipboardtext(bool value){
    getclipboardtext=value;
}
bool Config::isGetselectedtext(){
    return getselectedtext;
}
void Config::setSelectedtext(bool value){
    getselectedtext=value;
}

bool Config::isGetscreentext(){
    return getscreentext;
}
void Config::setScreentext(bool value){
    getscreentext=value;
}

bool Config::isShowquerylogo(){
    return showquerylogo;
}
void Config::setShowquerylogo(bool value){
    showquerylogo=value;
}
bool Config::isAutoaddword(){
    return autoaddword;
}
void Config::setAutoaddword(bool value){
    autoaddword=value;
}
