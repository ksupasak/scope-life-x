#include "capturesession.h"
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
CaptureSession::CaptureSession(QObject *parent)
{
    current_data["id"] = "123456-78";
    current_data["group"] = "colonoscopy";
    session_db_id = -1;
}

void CaptureSession::setMediaLibraryContext(MediaLibraryContext* library)
{
    this->library = library;


}

MediaLibraryContext* CaptureSession::getMediaLibrary()
{
    return this->library;
}



QString CaptureSession::generateImageCapturePath()
{   // internal only
    // path/date/time-hn-form/timestamp

    // the path
    QString path = library->generateInternalStoragePath(getData(),"image");

    QSqlDatabase *con = library->getDatabaseConnection();




    return path;
}

QString CaptureSession::generateVideoRecordPath()
{

    QString path = library->generateInternalStoragePath(getData(),"video");

    return path;
}

void CaptureSession::finsihedImageCapture(QString filename, QDateTime start_at)
{
    qDebug()<<"Finished Image Capture :"<< filename;
    QSqlQuery query;
    verifySession();

    if(session_db_id>0){
//        query.prepare("create table if not exists images (id integer primary key, session_id integer, path text, comment text,  datetime text, selected integer, sort_order integer ) ");

             query.prepare("insert into images(session_id, path, datetime) values (:session_id, :path, :datetime)");
                query.bindValue(":session_id", session_db_id);
                query.bindValue(":path",filename);
                query.bindValue(":datetime",start_at.toString("yyyy-MM-ddTHH:mm:ss"));

              if(query.exec()){

                  qDebug()<<"Insert Image "<<query.lastInsertId().toInt();

                  }else{
                    qDebug()<<"Insert exec error";
                 qDebug()<<query.lastError();
                 }


    }




}

void CaptureSession::finsishedVideoRecord(QString filename,QDateTime start_at,QDateTime stop_at)
{
    qDebug()<<"Finished Video Record :"<< filename;
    QSqlQuery query;
    verifySession();


    if(session_db_id>0){
//        query.prepare("create table if not exists images (id integer primary key, session_id integer, path text, comment text,  datetime text, selected integer, sort_order integer ) ");

        query.prepare("insert into videos(session_id, path, start_at, stop_at) values (:session_id, :path, :start_at, :stop_at)");
                query.bindValue(":session_id", session_db_id);
                query.bindValue(":path",filename);
                query.bindValue(":start_at",start_at.toString("yyyy-MM-ddTHH:mm:ss"));
                query.bindValue(":stop_at",stop_at.toString("yyyy-MM-ddTHH:mm:ss"));


              if(query.exec()){

                  qDebug()<<"Insert Video "<<query.lastInsertId().toInt();

                  }else{
                    qDebug()<<"Insert exec error";
                 qDebug()<<query.lastError();
                 }


    }


}

QHash<QString,QString> CaptureSession::getData()
{
    return this->current_data;
}

void CaptureSession::setCaptureSessionTemplate(CaptureSession *session_template)
{
    this->library = session_template->getMediaLibrary();
}

void CaptureSession::verifySession()
{
    QSqlQuery query;

    QHash<QString,QString> data = this->getData();
    QDateTime now = QDateTime::currentDateTime();

    if(session_db_id<0){
        query.prepare("insert into sessions(key, ref, name, comment, datetime) values (:key, :ref, :name,:comment, :datetime)");
        query.bindValue(":key",data["id"]);
        query.bindValue(":ref",data["ref"]);
        query.bindValue(":name",data["name"]);
        query.bindValue(":comment", data["comment"]);
        query.bindValue(":datetime",now.toString("yyyy-MM-ddTHH:mm"));
//        qDebug()<<query.
      if(query.exec()){

          session_db_id = query.lastInsertId().toInt();
          qDebug()<<"Insert Session "<<session_db_id;

          }else{
            qDebug()<<"Insert exec error";
         qDebug()<<query.lastError();
         }

    }

}

