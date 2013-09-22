/*
 *把ini配置改为sqlite储存，用户帐号安全稍微进步一些，而且避免用户不小心修改配置文件。
 *load（）函数负责第一次取数据库并赋值给类成员储存配置信息。
 *save（）把成员储存的配置信息写入到数据库。
 *此配置类为了同时打开多此数据库，设置为只可以实例化一个对象。
*/

#ifndef CONFIGDB_H
#define CONFIGDB_H

#include <QtCore>
#include <QtSql>

class ConfigDb
{
public:
    ~ConfigDb();
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

    static ConfigDb * getConfigDb();

protected:
    ConfigDb();
    void load();

private:
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

    QSqlDatabase dbLite;
    static ConfigDb * dbConfig;
};

#endif // CONFIGDB_H
