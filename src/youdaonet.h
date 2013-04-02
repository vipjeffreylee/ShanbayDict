#ifndef YOUDAONET_H
#define YOUDAONET_H

#include <QObject>
class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class YoudaoNet : public QObject
{
    Q_OBJECT
public:
    explicit YoudaoNet(QObject *parent = 0);
    
signals:
    void signalQueryFinished();
public slots:
    void httpfinished(QNetworkReply*);
public:
    void queryWord(const QString &word);
    QNetworkAccessManager * http;
};

#endif // YOUDAONET_H
