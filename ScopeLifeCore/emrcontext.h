#ifndef EMRCONTEXT_H
#define EMRCONTEXT_H

#include <QObject>
#include <QVector>
#include "emrsession.h"
#include "capturesession.h"


#define EMR_DIRECT_CAPTURE 0;
#define EMR_EMR_CAPTURE 1;
#define EMR_WEB_CAPTURE 2;
#define EMR_LIVE_CAPTURE 3;


class EMRContext
{
public:
    EMRContext();

    int getMode();

    void preload();

    // default is for today sessions
    QVector<EMRSession*> listEMRSessions();

    void setCaptureSessionTemplate(CaptureSession* capture);

    void setCurrentEMRSession(EMRSession* session);
    EMRSession* getCurrentEMRSession();

    QString getHost() const;
    void setHost(const QString &value);

protected:

    CaptureSession *capture_session_template;
    EMRSession *current_session;
    QVector<EMRSession*> list;
    int mode;

    QString host;

};

#endif // EMRCONTEXT_H
