#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <QDateTime>
#include <QObject>
#include <QUrl>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include "ScopeLifeCore_global.h"

class JOBQUEUE_EXPORT JobQueue
{
public:
    JobQueue(QUrl url, QString filename, QDateTime stamp);
    ~JobQueue();
    int getType() const;
    void setType(int value);

    QUrl getRequest() const;
    void setRequest(const QUrl &value);

    QString getFilename() const;
    void setFilename(const QString &value);

    QDateTime getStamp() const;
    void setStamp(const QDateTime &value);

    void process();

    QUrl getAttach_request() const;
    void setAttach_request( QUrl value);


private:
    int type;
    QUrl request;
    QUrl attach_request;
    QString filename;
    QDateTime stamp;


};

#endif // JOBQUEUE_H
