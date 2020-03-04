#include "emrsession.h"
#include <QDebug>
#include <QDateTime>
#include <QUrlQuery>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QThread>
EMRSession::EMRSession(QObject *parent):CaptureSession(parent)
{
    QDateTime now = QDateTime::currentDateTime();

    this->ref =  QString::number(now.toTime_t());

    snap_url = NULL;
    attach_url = NULL;
}

EMRSession::EMRSession(QObject *parent,CaptureSession* session_template, QString ref, QString hn,  QString emr_doc, QString full_name, QString gender, QString age):CaptureSession(parent)
{

    this->ref = ref;
    this->hn = hn;
    this->emr_doc = emr_doc;
    this->full_name = full_name;
    this->gender = gender;
    this->age = age;

    this->ssid_live = false;

}

QHash<QString, QString> EMRSession::getData()
{
    current_data["id"]  = ref;
    current_data["ref"] = hn;
    current_data["hn"] = hn ;
    current_data["full_name"] = full_name;
    current_data["gender"] = gender;
    current_data["name"] = emr_doc;
    current_data["age"] = age;
    current_data["comment"] = full_name+" "+gender+" "+age+"";
    return current_data;
}

QString EMRSession::getRef() const
{
    return ref;
}

void EMRSession::setRef(const QString &value)
{
    ref = value;
}

QString EMRSession::getHn() const
{
    return hn;
}

void EMRSession::setHn(const QString &value)
{
    hn = value;
}

QString EMRSession::getEMRDoc() const
{
    return emr_doc;
}

void EMRSession::setEMRDoc(const QString &value)
{
    emr_doc = value;
}

QString EMRSession::getFull_name() const
{
    return full_name;
}

void EMRSession::setFull_name(const QString &value)
{
    full_name = value;
}

QString EMRSession::getGender() const
{
    return gender;
}

void EMRSession::setGender(const QString &value)
{
    gender = value;
}

QString EMRSession::getAge() const
{
    return age;
}

void EMRSession::setAge(const QString &value)
{
    age = value;
}

void EMRSession::finsihedImageCapture(QString filename,QDateTime capture_at)
{
    CaptureSession::finsihedImageCapture(filename,capture_at);
    qDebug()<<"Finished Image Capture - EMR :"<< filename;



//    http://colo.emr-life.com

//    http://colo.emr-life.com/esm_image/113/snap?field_id=F8377840798&p_id=91&path=esm/colo/colo/test/colonoscopy/2017-05-28-592afec0790f9b5799000005/image&ref=test&ref_2=tste seff

//    /esm_image/113/snap?field_id=F8377840798&p_id=91&[ssid=ssid]&ref=test&ref_2=tste seff&snapcount=count&order=[stamp]

//    /esm_image/113/snap?field_id=F8377840798&ssid=1495991580&p_id=91&ref=35853-60&snapcount='+($('#snapcount').val()-1);

//    /esm_image/113/attach_to_gallery?p_id=91&field_id=F8377840798&ssid=1495991580

//    qDebug()<<"Thread : "<< QThread::currentThreadId();

    if(this->snap_url!=NULL){




//    QDateTime current = QDateTime::currentDateTime();
//    uint msecs = current.toTime_t();

//    QString ssid = this->getSsid();


//    QEventLoop eventLoop;
//    QNetworkAccessManager mgr;
//    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));


//      QUrl url(*snap_url);
      JobQueue * job = new JobQueue(*this->getFinalSnapUrl(),filename,capture_at);

      if(this->getSsidLive()){
          job->setAttach_request(*this->getFinalAttachUrl());
      }

//      emit uploadImageCapture(filename, capture_at, *snap_url);

      emit pushJobQueue(job);



//    QNetworkRequest req(url);

//    qDebug()<<"url = "<<url.toString();

//    QFile *file = new QFile(filename);

//    QString bound="margin"; //name of the boundary
//    QByteArray data(QString("--" + bound + "\r\n").toUtf8());
//    data.append("Content-Disposition: form-data; name=\"action\"\r\n\r\n");
//    data.append("testuploads.php\r\n"); //our script's name, as I understood. Please, correct me if I'm wrong
//    data.append("--" + bound + "\r\n"); //according to rfc 1867
//    data.append("Content-Disposition: form-data; name=\"image\"; filename=\"Chrysanthemum.jpg\"\r\n"); //name of the input is "uploaded" in my form, next one is a file name.
//    data.append("Content-Type: image/jpeg\r\n\r\n"); //data type
//    if (!file->open(QIODevice::ReadOnly));

//    data.append(file->readAll()); //let's read the file
//    file->close();
//    data.append("\r\n");
//    data.append("--" + bound + "--\r\n"); //closing boundary according to rfc 1867

//    QSslConfiguration conf = req.sslConfiguration();
//    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
//    req.setSslConfiguration(conf);

//    req.setRawHeader(QString("Content-Type").toUtf8(),QString("multipart/form-data; boundary=" + bound).toUtf8());
//    req.setRawHeader(QString("Content-Length").toUtf8(), QString::number(data.length()).toUtf8());

//    qDebug() << "Uploading" ;

////    this->visit->session->config->log("Uploading : "+path);


//    QNetworkReply *reply = mgr.post(req, data);
//    eventLoop.exec(); // blocks stack until "finished()" has been called


//    if (reply->error() == QNetworkReply::NoError) {
//        //success

//        QString res = QTextCodec::codecForMib(106)->toUnicode(reply->readAll());
//        //  ui->textEdit->setText(res);
//        qDebug() << "Success" <<res;
//        delete reply;




////         QNetworkRequest req( QUrl( QString(this->attach_url+"&ssid="+ssid) ) );

////         QSslConfiguration conf = req.sslConfiguration();
////         conf.setPeerVerifyMode(QSslSocket::VerifyNone);
////         req.setSslConfiguration(conf);

////         QNetworkReply *reply2 = mgr.get(req);
////         eventLoop.exec(); // blocks stack until "finished()" has been called

////         this->visit->session->config->log("Attaching image : "+path);


////        if (reply2->error() == QNetworkReply::NoError) {

////            qDebug()<<"Attached "<<path;


////        }

//    }
//    else {
//        //failure
//        qDebug() << "Failure" <<reply->errorString();
//        delete reply;
//    }


//    }

}







}

void EMRSession::finsishedVideoRecord(QString filename,QDateTime start_at,QDateTime stop_at )
{
    CaptureSession::finsishedVideoRecord(filename, start_at, stop_at);
    qDebug()<<"Finished Video Record - EMR :"<< filename;

}

void EMRSession::configureUrl(QUrl url)
{

    QUrlQuery query(url);


    QString path = query.queryItemValue("path");
    QStringList paths = path.split("/");
    QString emr_doc = paths.at(4);
    QString ids = paths.at(paths.size()-2);
    QString id = ids.split("-").last();
    qDebug()<<"session id = "<<id;
    setRef(id);
    setHn(query.queryItemValue("ref"));
    setFull_name(query.queryItemValue("ref_2"));
    setEMRDoc(emr_doc);
    QDateTime now = QDateTime::currentDateTime();
    ssid = QString::number(now.toTime_t());


    //    /esm_image/113/snap?field_id=F8377840798&p_id=91&path=esm/colo/colo/test/colonoscopy/2017-05-28-592afec0790f9b5799000005/image&ref=test&ref_2=tste seff

    //    /esm_image/113/snap?field_id=F8377840798&ssid=1495991580&p_id=91&ref=35853-60&snapcount='+($('#snapcount').val()-1);

    //    /esm_image/113/attach_to_gallery?p_id=91&field_id=F8377840798&ssid=1495991580


     snap_url = new QUrl(url);

     QUrlQuery snap_query(url);

     snap_query.addQueryItem("ssid",ssid);
     snap_url->setQuery(snap_query);
     qDebug()<<"SNAP Query: "<<snap_url->toString();


     QString u = url.path();
     u.replace("snap","attach_to_gallery");
     attach_url = new QUrl(url);
     attach_url->setPath(u);
     attach_url->setQuery(snap_query);
     qDebug()<<"Attach Query: "<<attach_url->toString();


}




QUrl* EMRSession::getSnap_url()
{
    return snap_url;
}

void EMRSession::setSnap_url(QUrl *value)
{
    snap_url = value;
}

QUrl* EMRSession::getAttach_url()
{
    return attach_url;
}

void EMRSession::setAttach_url(QUrl *value)
{
    attach_url = value;
}

QUrl* EMRSession::getFinalSnapUrl()
{
    if(this->ssid_live){
        QDateTime now = QDateTime::currentDateTime();
        ssid = QString::number(now.toTime_t());

        QUrlQuery snap_query(*this->snap_url);
        if(snap_query.hasQueryItem("ssid")){
            snap_query.removeQueryItem("ssid");
        }
        snap_query.addQueryItem("ssid",ssid);
        snap_url->setQuery(snap_query);


        QUrlQuery attach_query(*this->attach_url);
        if(attach_query.hasQueryItem("ssid")){
            attach_query.removeQueryItem("ssid");
        }
        attach_query.addQueryItem("ssid",ssid);
        attach_url->setQuery(attach_query);

    }

    return snap_url;

}

QUrl* EMRSession::getFinalAttachUrl()
{
    return attach_url;
}

CoreLib *EMRSession::getCore() const
{
    return core;
}

void EMRSession::setCore(CoreLib *value)
{
    core = value;
}

QString EMRSession::getSsid() const
{
    return ssid;
}

void EMRSession::setSsid(const QString &value)
{
    ssid = value;
}

void EMRSession::finish()
{
//    //      QUrl url(*snap_url);
//          JobQueue * job = new JobQueue(*attach_url);

//    //      emit uploadImageCapture(filename, capture_at, *snap_url);

//          emit pushJobQueue(job);
}

bool EMRSession::getSsidLive() const
{
    return ssid_live;
}

void EMRSession::setSsidLive(bool value)
{
    ssid_live = value;
}

