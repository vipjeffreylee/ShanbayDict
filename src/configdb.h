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
