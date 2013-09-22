#include "configdb.h"

ConfigDb * ConfigDb::dbConfig = nullptr;

ConfigDb::ConfigDb()
{
    dbLite = QSqlDatabase::addDatabase("QSQLIte","ShanBayDiat");
    dbLite.setDatabaseName("./seadict/Config.db");
    dbLite.open();
    load();
}

ConfigDb::~ConfigDb()
{
    if (dbConfig != nullptr)
    {
        dbLite.close();
        delete dbConfig;
        dbConfig = nullptr;
    }
}

ConfigDb * ConfigDb::getConfigDb()
{
    if (dbConfig == nullptr)
    {
        dbConfig = new ConfigDb();
    }
    return dbConfig;
}

void  ConfigDb::load()
{
    QSqlQuery sqlQue(dbLite);
    if(sqlQue.exec("sqlQue * from setting"))
    {
        while (sqlQue.next())
        {
            if(sqlQue.value("Key").toString() == "username")
            {
                this->username = sqlQue.value("Value").toString();
                continue;
            }
            if(sqlQue.value("Key").toString() == "userpass")
            {
                this->userpass = sqlQue.value("Vaule").toString();
                continue;
            }
            if(sqlQue.value("Key").toString() == "savepass")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->savepass = true;
                }
                else
                {
                    this->savepass = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "autologin")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->autologin = true;
                }
                else
                {
                    this->autologin = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "autospeak")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->autospeak = true;
                }
                else
                {
                    this->autospeak = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "getscreentext")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->getscreentext = true;
                }
                else
                {
                    this->getscreentext = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "getclipboardtext")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->getclipboardtext = true;
                }
                else
                {
                    this->getclipboardtext = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "getselectedtext")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->getselectedtext = true;
                }
                else
                {
                    this->getselectedtext = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "showquerylogo")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->showquerylogo = true;
                }
                else
                {
                    this->showquerylogo = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "autorun")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->autorun = true;
                }
                else
                {
                    this->autorun = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "autohide")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->autohide = true;
                }
                else
                {
                    this->autohide = false;
                }
                continue;
            }
            if(sqlQue.value("Key").toString() == "autoaddword")
            {
                if (sqlQue.value("Vaule").toString() == "true")
                {
                    this->autoaddword = true;
                }
                else
                {
                    this->autoaddword = false;
                }
                continue;
            }
        }
    }
    else
    {
        sqlQue.exec("CREATE TABLE [setting] ([Key] [NVARCHAR(36)] NOT NULL, [Vaule] [NVARCHAR(36)],  CONSTRAINT [] PRIMARY KEY ([Key]));");
        sqlQue.exec("Insert into setting (Key,Vaule) values('autospeak','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('getscreentext','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('getclipboardtext','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('getsqlQueedtext','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('showquerylogo','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('autohide','true') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('autorun','false') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('autoaddword','false') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('autologin','false') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('savepass','false') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('username','') ");
        sqlQue.exec("Insert into setting (Key,Vaule) values('userpass','') ");
    }
}

void  ConfigDb::save()
{
     QSqlQuery tmp(dbLite);
     tmp.exec(QString("update sett set Vaule='%1' where Key='username'").arg(this->username));
     tmp.exec(QString("update sett set Vaule='%1' where Key='userpass'").arg(this->userpass));
     if (this->autohide)
         tmp.exec("update sett set Vaule='true' where Key='autohide'");
     else
         tmp.exec("update sett set Vaule='false' where Key='autohide'");

     if (this->savepass)
         tmp.exec("update sett set Vaule='true' where Key='savepass'");
     else
         tmp.exec("update sett set Vaule='false' where Key='savepass'");

     if (this->autologin)
         tmp.exec("update sett set Vaule='true' where Key='autologin'");
     else
         tmp.exec("update sett set Vaule='false' where Key='autologin'");

     if (this->autospeak)
         tmp.exec("update sett set Vaule='true' where Key='autospeak'");
     else
         tmp.exec("update sett set Vaule='false' where Key='autospeak'");

     if (this->getscreentext)
         tmp.exec("update sett set Vaule='true' where Key='getscreentext'");
     else
         tmp.exec("update sett set Vaule='false' where Key='getscreentext'");

     if (this->getclipboardtext)
         tmp.exec("update sett set Vaule='true' where Key='getclipboardtext'");
     else
         tmp.exec("update sett set Vaule='false' where Key='getclipboardtext'");

     if (this->getselectedtext)
         tmp.exec("update sett set Vaule='true' where Key='getselectedtext'");
     else
         tmp.exec("update sett set Vaule='false' where Key='getselectedtext'");

     if (this->showquerylogo)
         tmp.exec("update sett set Vaule='true' where Key='showquerylogo'");
     else
         tmp.exec("update sett set Vaule='false' where Key='showquerylogo'");

     if (this->autorun)
         tmp.exec("update sett set Vaule='true' where Key='autorun'");
     else
         tmp.exec("update sett set Vaule='false' where Key='autorun'");

     if (this->autoaddword)
         tmp.exec("update sett set Vaule='true' where Key='autoaddword'");
     else
         tmp.exec("update sett set Vaule='false' where Key='autoaddword'");
}

QString  ConfigDb::getUsername() const
{
    return this->username;
}

void  ConfigDb::setUsername(const QString &name)
{
    this->username = name;
}

QString  ConfigDb::getUserpass() const
{
    return this->userpass;
}

void  ConfigDb::setUserpass(const QString &text)
{
    this->userpass = text;
}

bool  ConfigDb::isSavepass() const
{
    return this->savepass;
}

void  ConfigDb::setSavepass(bool value)
{
    this->savepass = value;
}

bool  ConfigDb::isAutologin() const
{
    return this->autologin;
}

void  ConfigDb::setAutologin(bool value)
{
    this->autologin = value;
}

bool  ConfigDb::isAutohide() const
{
    return this->autohide;
}

void  ConfigDb::setAutohide(bool value)
{
    this->autohide = value;
}

bool  ConfigDb::isAutospeak() const
{
    return  this->autospeak ;
}

void  ConfigDb::setAutospeak(bool value)
{
    this->autospeak = value;
}

bool  ConfigDb::isAutorun() const
{
    return this->autorun;
}

void  ConfigDb::setAutorun(bool value)
{
    this->autorun = value;
}

bool  ConfigDb::isGetclipboardtext() const
{
    return this->getclipboardtext;
}

void  ConfigDb::setClipboardtext(bool value)
{
    this->getclipboardtext = value;
}

bool  ConfigDb::isGetselectedtext() const
{
    return  this->getselectedtext;
}

void  ConfigDb::setSelectedtext(bool value)
{
    this->getselectedtext = value;
}

bool  ConfigDb::isGetscreentext() const
{
    return this->getscreentext;
}

void  ConfigDb::setScreentext(bool value)
{
    this->getscreentext = value;
}

bool  ConfigDb::isShowquerylogo() const
{
    return this->showquerylogo;
}

void  ConfigDb::setShowquerylogo(bool value)
{
    this->showquerylogo = value;
}

bool  ConfigDb::isAutoaddword() const
{
    return this->autoaddword;
}

void  ConfigDb::setAutoaddword(bool value)
{
    this->autoaddword = value;
}
