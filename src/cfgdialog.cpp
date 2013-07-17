
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
#include "cfgdialog.h"
#include "ui_cfgdialog.h"
#include "dict.h"
CfgDialog::CfgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgDialog)
{
    ui->setupUi(this);
#ifndef Q_OS_WIN
    ui->autorunCheckBox->setVisible(false);
#endif
    connect(ui->okPushButton,SIGNAL(clicked()),this,SLOT(savecfgClick()));
    connect(ui->cancelPushButton,SIGNAL(clicked()),this,SLOT(cancelClick()));
}

CfgDialog::~CfgDialog()
{
    delete ui;
}

void CfgDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void CfgDialog::loadcfg()
{
    ui->screenCheckBox->setChecked(DICT::cfg->isGetscreentext());
    ui->clipboardCheckBox->setChecked(DICT::cfg->isGetclipboardtext());
    ui->selectedCheckBox->setChecked(DICT::cfg->isGetselectedtext());
    ui->showlogoCheckBox->setChecked(DICT::cfg->isShowquerylogo());
    ui->autologinCheckBox->setChecked(DICT::cfg->isAutologin());
    ui->autospeakCheckBox->setChecked(DICT::cfg->isAutospeak());
    ui->autoaddwordCheckBox->setChecked(DICT::cfg->isAutoaddword());
    ui->autorunCheckBox->setChecked(DICT::cfg->isAutorun());
    ui->autohideCheckBox->setChecked(DICT::cfg->isAutohide());
}

void CfgDialog::cancelClick()
{
    this->hide();
}

void CfgDialog::savecfgClick()
{
    DICT::cfg->setScreentext(ui->screenCheckBox->checkState());
    DICT::cfg->setClipboardtext(ui->clipboardCheckBox->checkState());
    DICT::cfg->setSelectedtext(ui->selectedCheckBox->checkState());
    DICT::cfg->setShowquerylogo(ui->showlogoCheckBox->checkState());
    DICT::cfg->setAutologin(ui->autologinCheckBox->checkState());
    DICT::cfg->setAutospeak(ui->autospeakCheckBox->checkState());
    DICT::cfg->setAutoaddword(ui->autoaddwordCheckBox->checkState());
    DICT::cfg->setAutohide(ui->autohideCheckBox->checkState());

#if defined(Q_OS_WIN)
    if (DICT::cfg->isAutorun() != ui->autorunCheckBox->isChecked())
    {
        DICT::cfg->setAutorun(ui->autorunCheckBox->checkState());
        QSettings *reg = new QSettings(
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
                "\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        //开机自动运行
        if (DICT::cfg->isAutorun())
        {
            reg->setValue("ShanbayDict", 
                    QApplication::applicationFilePath().replace('/','\\'));
        }
        else
        {
            reg->setValue("ShanbayDict", "");
        }
        reg->deleteLater();
    }
#endif

    DICT::updateCfg();
    this->hide();
}
