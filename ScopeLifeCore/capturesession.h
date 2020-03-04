#ifndef CAPTURESESSION_H
#define CAPTURESESSION_H

#include <QObject>
#include "medialibrarycontext.h"
#include <QHash>
class CaptureSession : public QObject
{
        Q_OBJECT
public:
    CaptureSession(QObject *parent);

    void setMediaLibraryContext(MediaLibraryContext* library);
    MediaLibraryContext *getMediaLibrary();

    QString generateImageCapturePath();
    QString generateVideoRecordPath();

    virtual void finsihedImageCapture(QString filename,QDateTime start_at);
    virtual void finsishedVideoRecord(QString filename,QDateTime start_at,QDateTime stop_at );

    virtual QHash<QString,QString> getData();

    void setCaptureSessionTemplate(CaptureSession *session_template);

    void verifySession();


signals:


protected:
    int session_db_id=0;
    MediaLibraryContext* library;
    QHash<QString,QString> current_data;

};

#endif // CAPTURESESSION_H
