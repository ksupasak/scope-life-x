#include "medialibrarycontext.h"
#include <QDir>
#include <QStringList>
#include <QDateTime>
#include <QDebug>



MediaLibraryContext::MediaLibraryContext(CoreLib *core)
{
    this->core = core;

    QString home_path = core->getDefaultPath()->toUtf8();

    if(!QDir(home_path).exists()){

        if(QDir().mkdir(home_path)==false){
            qDebug()<<"Unable to Create Dir :"<<home_path;
        }else{
            qDebug()<<"Create Dir :"<<home_path;
        }
    }

    QString home_web = home_path+QDir::separator()+"web";

    if(!QDir(home_web).exists()){

        if(QDir().mkdir(home_web)==false){
            qDebug()<<"Unable to Create Web Dir :"<<home_web;
        }else{
            qDebug()<<"Create Web Dir :"<<home_web;
        }
    }





    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(home_path+QDir::separator()+"medialib.sqlite");
    if(!db.open())
    {
        qDebug()<<"Error";
        error = db.lastError().text();

    }else
        qDebug()<<"OK";

    checkSchema();

}

void MediaLibraryContext::checkSchema()
{

    /*
    SELECT name FROM sqlite_master WHERE type='table' AND name='table_name';
    create table if not exists TableName (col1 typ1, ..., colN typN)*/


    QSqlQuery query;

    query.prepare("create table if not exists sessions (id integer primary key, key text, ref text, name text, comment text, datetime text ) ");

    if(query.exec()){
     qDebug()<<"session table is ok";
     }else{
     qDebug()<<query.lastError();
     }

    query.prepare("create table if not exists images (id integer primary key, session_id integer, path text, comment text,  datetime text, selected integer, sort_order integer ) ");

    if(query.exec()){
     qDebug()<<"image table is ok";
     }else{
     qDebug()<<query.lastError();
     }

    query.prepare("create table if not exists videos (id integer primary key, session_id integer, path text,comment text, datetime text, start_at integer, stop_at integer ) ");

    if(query.exec()){
     qDebug()<<"video table is ok";
     }else{
     qDebug()<<query.lastError();
     }

//    CREATE TABLE contacts (
//     contact_id integer PRIMARY KEY,
//     first_name text NOT NULL,
//     last_name text NOT NULL,
//     email text NOT NULL UNIQUE,
//     phone text NOT NULL UNIQUE
//    );


//    query.prepare("insert into patient (date, station, slot, name) values (:date, :station, :slot, :name)");
//            query.bindValue(":date",date);
//            query.bindValue(":station",station);
//            query.bindValue(":slot",slot);
//            query.bindValue(":name",name);

//         qDebug()<<"insert is wait";
//            if(query.exec()){
//               qDebug()<<"insert is ok";
//            }else{
//                qDebug()<<query.lastError();
//            }


}

QString MediaLibraryContext::generateInternalStoragePath(QString type)
{
    return    generateInternalStoragePath(this->params,type);
}

QString MediaLibraryContext::generateInternalStoragePath(QHash<QString, QString> data, QString type)
{
//    QString internal_path = "/Users/soup/Desktop/db";


//    current_data["id"]  = ref;
//    current_data["ref"] = ref;
//    current_data["hn"] = hn ;  ok
//    current_data["full_name"] = full_name;
//    current_data["gender"] = gender;
//    current_data["name"] = emr_doc; ok
//    current_data["age"] = age;


//        QString id = data.value("id");
//        QString ref = data.value("ref");
//        QString name = data.value("name");

//    QString path = internal_path  + QDir::separator() + id  + QDir::separator() + group  + QDir::separator();





    QHash<QString, QString> lookup(data);
    QDateTime now = QDateTime::currentDateTime();


          lookup["home"] = QDir::homePath();
          lookup["media"] = type;


          lookup["date"] = now.toString("yyyy-MM-dd");
          lookup["datetime"] = now.toString("yyyy-MM-dd-hh-mm-ss");
          lookup["stamp"] = QString::number(now.toTime_t());

          QString hn = lookup["hn"];
          if(hn.indexOf("/")>0)
          hn.replace(hn.indexOf("/"),1,"-");
          lookup["hn"] = hn;

//        QString pattern = ":home/Desktop/db/:date/:hn/:name/:id/:hn-:full_name-:stamp";

        QString pattern = ":home/scopelife/db/:date/:hn/:doc_name/:id/:hn|:full_name|:stamp";


        QStringList result;

////        result << replacePattern(pattern,lookup);




//            return

        QStringList paths = pattern.split("/");
        for(int i=0;i<paths.size();i++){
            result<<replacePattern(paths[i],lookup);
        }
        qDebug()<<result;


        QString filename = result.last();
        result.pop_back();
        QString path = result.join("/");

        qDebug()<<"path="<<path<<", filename="<<filename;
        QStringList serial;

        for(int i=0;i<result.size();i++){
           serial<<result[i];
           QString subdir = serial.join("/");
           if(QDir(subdir).exists()){
//               qDebug()<<"Found Dir :"<<subdir;
           }else{
               if(QDir().mkdir(subdir)==false){
                   return NULL;
               }else{
                   qDebug()<<"Create Dir :"<<subdir;
               }
           }

        }

        result<<filename;

        path = result.join("/");

        qDebug()<<"File gen = "<<path;


        return path;

}


QString MediaLibraryContext::replacePattern(QString pattern, QHash<QString, QString> lookup)
{
    QStringList global;

    QStringList glist = pattern.split("/");

    for(int j=0;j<glist.size();j++){

    QStringList result;
    QStringList list = glist[j].split("|");

    for(int i = 0 ;i<list.size();i++){
        QString tag = list[i];
        QString var = tag.mid(1);
        if(lookup.contains(var)){
            result << lookup.value(var);
        }else{
            result << tag ;
        }

    }
        global<<result.join("_");
    }
    return global.join("/");

}

QSqlDatabase *MediaLibraryContext::getDatabaseConnection()
{
    return &db;
}

CoreLib *MediaLibraryContext::getCore() const
{
    return core;
}

void MediaLibraryContext::setCore(CoreLib *value)
{
    core = value;
}

QHash<QString, QString> MediaLibraryContext::getParams() const
{
    return params;
}

void MediaLibraryContext::setParams(const QHash<QString, QString> &value)
{
    params = value;
}

