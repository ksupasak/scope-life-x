#ifndef EMRSESSION_H
#define EMRSESSION_H
#include "capturesession.h"
#include <QObject>
#include <QDateTime>
#include <QUrl>
#include "jobqueue.h"
#include "corelib.h"

class EMRSession : public CaptureSession
{

    Q_OBJECT




public:


    EMRSession(QObject *parent);
    EMRSession(QObject *parent, CaptureSession* session_template, QString ref, QString hn, QString emr_doc, QString full_name, QString gender, QString age);

    virtual QHash<QString,QString> getData();

    QString getRef() const;
    void setRef(const QString &value);

    QString getHn() const;
    void setHn(const QString &value);

    QString getEMRDoc() const;
    void setEMRDoc(const QString &value);

    QString getFull_name() const;
    void setFull_name(const QString &value);

    QString getGender() const;
    void setGender(const QString &value);

    QString getAge() const;
    void setAge(const QString &value);

    virtual void finsihedImageCapture(QString filename, QDateTime capture_at);
    virtual void finsishedVideoRecord(QString filename, QDateTime start_at, QDateTime stop_at);

    void configureUrl(QUrl url);

    QUrl* getSnap_url() ;
    void setSnap_url( QUrl* value);

    QUrl* getAttach_url() ;
    void setAttach_url( QUrl *value);


    QUrl *getFinalSnapUrl();
    QUrl *getFinalAttachUrl();

    CoreLib *core;

    QString getSsid() const;
    void setSsid(const QString &value);

    void finish();


    bool getSsidLive() const;
    void setSsidLive(bool value);

    CoreLib *getCore() const;
    void setCore(CoreLib *value);

signals:

    void pushJobQueue(JobQueue* job);

protected:
    QString ref;
    QString hn;
    QString emr_doc;
    QString full_name;
    QString gender;
    QString age;

    bool ssid_live;

    QString ssid;

    QUrl *snap_url;
    QUrl *attach_url;



};

#endif // EMRSESSION_H
