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
#include "picturebutton.h"
//#include <QDebug>
PictureButton::PictureButton(QWidget *parent) :
    QPushButton(parent)
{
}
void PictureButton::enterEvent(QEvent *event)
{
    //qDebug()<<"enterEvent"<<hoverIcon.name();
    setIcon(hoverIcon);
    this->QPushButton::enterEvent(event);

}

void PictureButton::leaveEvent(QEvent *event)
{
    //qDebug()<<"leaveEvent";
    setIcon(normalIcon);
    this->QPushButton::leaveEvent(event);

}
void PictureButton::setPicture(const QString normal, const QString hover){
    normalIcon=QIcon(normal);
    hoverIcon=QIcon(hover);
    setIcon(normalIcon);
}
