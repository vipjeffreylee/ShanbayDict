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
#include "englishword.h"
EnglishWord::EnglishWord()
{

}
EnglishWord::EnglishWord(const EnglishWord &w){

    name=w.name;
    learning_id=w.learning_id;
    definition=w.definition;
    en_definitions=w.en_definitions;
    pron=w.pron;
    audio=w.audio;
    examples=w.examples;

}

EnglishWord::~EnglishWord(){
}
bool EnglishWord::operator ==(const EnglishWord &w){
    return name==w.name;
}
void EnglishWord::clear(){
    this->name.clear();
    this->learning_id.clear();
    this->definition.clear();
    this->en_definitions.clear();
    this->pron.clear();
    this->audio.clear();
    this->examples.clear();
}
QString EnglishWord::formatDefinition(){
    return QString("<span style='color:#000000;font-size:15px;font-weight: bolder;font-family:Arial, Helvetica, Geneva;' >%1</span><br><font color='#000000' face='Arial, Helvetica, Geneva'>%2</font>")
            .arg(definition.replace("\n",""))
            .arg(en_definitions);
}
QString EnglishWord::formatNameAndPron(){
    return QString("<span style='font-family:Arial, Helvetica, Geneva;color:#C09;font-size:18px;'><b>%1</b></span><span style='font-family:Segoe UI, Verdana, Lucida Sans Regular, Lucida Sans Unicode, Arial, sans-serif;color:Gray;font-size:15px;'>[%2]</span>")
            .arg(name)
            .arg(pron);
}
QString EnglishWord::formatExamples(){
    QString retstr;
    for(int i=0;i<examples.size();i++){
        retstr.append(QString("%1.<font face='Arial, Helvetica, Geneva'> %2<font color='#C09'><b>%3</b></font>%4</font><br><font color='darkcyan'>%5</font><br>")
                             .arg(i+1)
                             .arg(examples.at(i).value("first").toString())
                             .arg(examples.at(i).value("mid").toString())
                             .arg(examples.at(i).value("last").toString())
                             .arg(examples.at(i).value("translation").toString())
                      ).replace('\"',"&quot;");
    }
    return retstr;
}
