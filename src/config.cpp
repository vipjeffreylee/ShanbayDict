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
    settings = new QSettings("shanbay.ini", QSettings::IniFormat);
    load();
}

Config::~Config()
{
    settings->sync();
    settings->deleteLater();
}

void Config::load()
{
    _config["username"] = settings->value("username", 
            "").toString();
    _config["userpass"] = settings->value("userpass", 
            "").toString();
    _config["savepass"] = settings->value("savepass", 
            false).toBool();
    _config["autologin"] = settings->value("autologin", 
            false).toBool();
    _config["autospeak"] = settings->value("autospeak", 
            true).toBool();
    _config["getscreentext"] = settings->value(
            "getscreentext", true).toBool();
#ifdef Q_OS_WIN
    _config["getclipboardtext"] = settings->value(
            "getclipboardtext", true).toBool();
    _config["getselectedtext"] = settings->value(
            "getselectedtext", false).toBool();
#else
    _config["getclipboardtext"] = settings->value(
            "getclipboardtext", false).toBool();
    _config["getselectedtext"] = settings->value(
            "getselectedtext", true).toBool();
#endif
    _config["showquerylogo"] = settings->value(
            "showquerylogo", true).toBool();
    _config["autorun"] = settings->value("autorun", 
            false).toBool();
    _config["autohide"] = settings->value("autohide", 
            true).toBool();
    _config["autoaddword"] = settings->value("autoaddword", 
            false).toBool();
}

void Config::save()
{
    QMapIterator<QString, QVariant> it(_config);
    while (it.hasNext())
    {
        it.next();
        settings->setValue(it.key(), it.value());
    }

    /*
    settings->setValue("username", username);
    settings->setValue("userpass", userpass);
    settings->setValue("savepass", savepass);
    settings->setValue("autologin", autologin);
    settings->setValue("autospeak", autospeak);
    settings->setValue("getscreentext", getscreentext);
    settings->setValue("getclipboardtext", getclipboardtext);
    settings->setValue("getselectedtext", getselectedtext);
    settings->setValue("showquerylogo", showquerylogo);
    settings->setValue("autorun", autorun);
    settings->setValue("autohide", autohide);
    settings->setValue("autoaddword", autoaddword);
    */
    settings->sync();
}

QString Config::getUsername() const
{
    return _config.contains("username") ?
        _config["username"].toString() : QString();
}

void Config::setUsername(const QString &name)
{
    _config["username"] = name;
}

QString Config::getUserpass() const
{
    return _config.contains("userpass") ?
        _config["userpass"].toString() : QString();
}

void Config::setUserpass(const QString &text)
{
    _config["userpass"] = text;
}

bool Config::isSavepass() const
{
    return _config.contains("savepass") ?
        _config["savepass"].toBool() : false;
}

void Config::setSavepass(bool value)
{
    _config["savepass"] = value;
}

bool Config::isAutologin() const
{
    return _config.contains("autologin") ?
        _config["autologin"].toBool() : false;
}

void Config::setAutologin(bool value)
{
    _config["autologin"] = value;
}

bool Config::isAutohide() const
{
    return _config.contains("autohide") ?
        _config["autohide"].toBool() : true;
}

void Config::setAutohide(bool value)
{
    _config["autohide"] = value;
}

bool Config::isAutospeak() const
{
    return _config.contains("autospeak") ?
        _config["autospeak"].toBool() : true;
}

void Config::setAutospeak(bool value)
{
    _config["autospeak"] = value;
}

bool Config::isAutorun() const
{
    return _config.contains("autorun") ?
        _config["autorun"].toBool() : false;
}

void Config::setAutorun(bool value)
{
    _config["autorun"] = value;
}

bool Config::isGetclipboardtext() const
{
    return _config.contains("getclipboardtext") ?
        _config["getclipboardtext"].toBool() : true;
}

void Config::setClipboardtext(bool value)
{
    _config["getclipboardtext"] = value;
}

bool Config::isGetselectedtext() const
{
    return _config.contains("getselectedtext") ?
        _config["getselectedtext"].toBool() : false;
}

void Config::setSelectedtext(bool value)
{
    _config["getselectedtext"] = value;
}

bool Config::isGetscreentext() const
{
    return _config.contains("getscreentext") ?
        _config["getscreentext"].toBool() : true;
}

void Config::setScreentext(bool value)
{
    _config["getscreentext"] = value;
}

bool Config::isShowquerylogo() const
{
    return _config.contains("showquerylogo") ?
        _config["showquerylogo"].toBool() : true;
}

void Config::setShowquerylogo(bool value)
{
    _config["showquerylogo"] = value;
}

bool Config::isAutoaddword() const
{
    return _config.contains("autoaddword") ?
        _config["autoaddword"].toBool() : false;
}

void Config::setAutoaddword(bool value)
{
    _config["autoaddword"] = value;
}
