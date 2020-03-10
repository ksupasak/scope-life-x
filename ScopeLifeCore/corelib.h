#ifndef CORELIB_H
#define CORELIB_H

#include "corelib_global.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDateTime>
#include <QVector>
#include "jobqueue.h"
#include "session.h"

struct LogText{
    QDateTime stamp;
    QString msg;
};


class CORELIBSHARED_EXPORT CoreLib
{

public:
    CoreLib();
    QString* getDefaultPath();
    void setDefaultPath(QString *value);

    void loadConfig();
    void saveConfig();

    void setValue(QString key, QVariant value);
    QVariant getValue(QString key);
    QString getStringValue(QString key);
    QString getStringValue(QString key, QString default_value);

    bool has(QString key);

    void log(QString msg);
    QString getLogText();


    void pushJobQueue(JobQueue *job);
    void processQueue();

    Session *getCurrentSession() const;
    void setCurrentSession(Session *value);
    bool hasCurrentSession();
    void finishSession();



private:
    QString * default_path;
    QVariantMap config;

    Session *current_session=NULL;


    QVector<JobQueue*> *queues;
    QVector<LogText*> logs;

};

#endif // CORELIB_H
