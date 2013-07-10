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
#include <QApplication>
#include "dict.h"


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
#ifdef Q_OS_LINUX
    QFont font;
    font.setFamily("WenQuanYi Micro Hei");
    qApp->setFont(font);
#endif
    //http://media.shanbay.com/audio/us/get_ready.mp3
    //http://media.shanbay.com/sounds/char.mp3
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb18030"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    //扇贝词典版本信息
    DICT::versioninformation=QObject::tr("扇贝词典1.3.2");
    //所有使用本软件全部或者部分代码的程序设计人员请保留lience信息，并在所发布的软件关于窗口中进行显示。
    DICT::licenceinformation=
    QObject::tr("<h2>%1</h2>"
                        "扇贝词典依据<a href='http://www.shanbay.com'><b>扇贝网</b></a>公开的API设计，扇贝网是最专业的背单词网站<br> "
                        "<p>Copyright(C) 2013 Jeffrey Lee  All rights reserved.</p>"
                        "<p>完全遵循LGPL协议,未经作者允许不得作为商业用途。<a href='http://vipjeffreylee.github.com/ShanbayDict/'><b>扇贝词典开源网址</b></a></p>"
                        "<p><h3>软件作者:Jeffrey Lee<br>email:vipjeffreylee@gmail.com<br>新浪微博：<a href='http://weibo.com/207899158'>http://weibo.com/207899158</a><br>"
                        "QQ:53336158 扇贝词典QQ群：130406877</h3</p>"
                        "<p>本软件有多个平台的版本包含linux、mac和windows。</p>").arg(DICT::versioninformation);
    qApp->setQuitOnLastWindowClosed(true);
    DICT::login();
    return a.exec();
}
