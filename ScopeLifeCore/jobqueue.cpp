#include "jobqueue.h"
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QUrlQuery>
JobQueue::JobQueue(QUrl request, QString filename, QDateTime stamp)
{
    this->type = 1;
    this->request = request;
    this->filename = filename;
    this->stamp = stamp;
    this->attach_request = QUrl("");
}

int JobQueue::getType() const
{
    return type;
}

void JobQueue::setType(int value)
{
    type = value;
}

QUrl JobQueue::getRequest() const
{
    return request;
}

void JobQueue::setRequest(const QUrl &value)
{
    request = value;
}

QString JobQueue::getFilename() const
{
    return filename;
}

void JobQueue::setFilename(const QString &value)
{
    filename = value;
}

QDateTime JobQueue::getStamp() const
{
    return stamp;
}

void JobQueue::setStamp(const QDateTime &value)
{
    stamp = value;
}

void JobQueue::process()
{

    qDebug()<<"Start upload";

    QDateTime current = QDateTime::currentDateTime();
    uint msecs = current.toTime_t();

    QString ssid = "12345";


    QEventLoop eventLoop;
    QNetworkAccessManager mgr;

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl url(this->request);

    QUrlQuery query(url);

    query.addQueryItem("order",QString::number(this->stamp.toTime_t()));

    url.setQuery(query);

    QNetworkRequest req(url);


    qDebug()<<"url = "<<url.toString();

    QFile *file = new QFile(this->getFilename());

    QString bound="margin"; //name of the boundary
    QByteArray data(QString("--" + bound + "\r\n").toUtf8());
    data.append("Content-Disposition: form-data; name=\"action\"\r\n\r\n");
    data.append("testuploads.php\r\n"); //our script's name, as I understood. Please, correct me if I'm wrong
    data.append("--" + bound + "\r\n"); //according to rfc 1867
    data.append("Content-Disposition: form-data; name=image; filename=img.jpg\r\n"); //name of the input is "uploaded" in my form, next one is a file name.
    data.append("Content-Type: image/jpeg\r\n\r\n"); //data type
    if (!file->open(QIODevice::ReadOnly));

    data.append(file->readAll()); //let's read the file
    file->close();
    data.append("\r\n");
    data.append("--" + bound + "--\r\n"); //closing boundary according to rfc 1867

    QSslConfiguration conf = req.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    req.setSslConfiguration(conf);

    req.setRawHeader(QString("Content-Type").toUtf8(),QString("multipart/form-data; boundary=" + bound).toUtf8());
    req.setRawHeader(QString("Content-Length").toUtf8(), QString::number(data.length()).toUtf8());

    qDebug() << "Uploading" ;

//    this->visit->session->config->log("Uploading : "+path);

    QNetworkReply *reply = mgr.post(req, data);
    eventLoop.exec(); // blocks stack until "finished()" has been called


    if (reply->error() == QNetworkReply::NoError) {
        //success
//        core->log("Upload completed.");


        QString res = QTextCodec::codecForMib(106)->toUnicode(reply->readAll());
        qDebug() << "Success" <<res;
        delete reply;



        if(this->attach_request.toString()!=""){
         qDebug()<<this->attach_request;
         QNetworkRequest req( this->attach_request );

         QSslConfiguration conf = req.sslConfiguration();
         conf.setPeerVerifyMode(QSslSocket::VerifyNone);
         req.setSslConfiguration(conf);

         QNetworkReply *reply2 = mgr.get(req);
         eventLoop.exec(); // blocks stack until "finished()" has been called

//         this->visit->session->config->log("Attaching image : "+path);


        if (reply2->error() == QNetworkReply::NoError) {

            qDebug()<<"Attached ";
//            core->log("Attach completed.");

        }
        }



    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
//        core->log("ERR : "+reply->errorString());
        delete reply;
    }
}

QUrl JobQueue::getAttach_request() const
{
    return attach_request;
}

void JobQueue::setAttach_request(QUrl value)
{
    attach_request = value;
}

//CoreLib *JobQueue::getCore() const
//{
//    return core;
//}

//void JobQueue::setCore(CoreLib *value)
//{
//    core = value;
//}
