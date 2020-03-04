#include "emrcontext.h"

EMRContext::EMRContext()
{
    mode = EMR_WEB_CAPTURE;

}

int EMRContext::getMode()
{
        return mode;
}

void EMRContext::setCaptureSessionTemplate(CaptureSession *capture)
{
    this->capture_session_template = capture;
}


void EMRContext::preload()
{
//    list.append(new EMRSession(capture_session_template, "12345","3444-34","colonoscopy","Supasak","Male", "34"));
//    list.append(new EMRSession(capture_session_template, "12345","3444-34","gastroscopy","Supasak","Male", "34"));
}

QVector<EMRSession *> EMRContext::listEMRSessions()
{
    return this->list;
}



void EMRContext::setCurrentEMRSession(EMRSession *session)
{
    this->current_session = session;
}

EMRSession *EMRContext::getCurrentEMRSession()
{
    return current_session;
}

QString EMRContext::getHost() const
{
    return host;
}

void EMRContext::setHost(const QString &value)
{
    host = value;
}

