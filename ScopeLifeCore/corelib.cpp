#include "corelib.h"
#include <QDir>
#include <QDebug>

CoreLib::CoreLib()
{
    qDebug()<<"init";
    default_path = new QString(QDir::homePath()+QDir::separator()+"scopelife") ;


    queues = new QVector<JobQueue*>();


}

QString* CoreLib::getDefaultPath()
{
//    qDebug()<<"getdefault "<<*this->default_path;
    return default_path;
}

void CoreLib::setDefaultPath(QString *value)
{
    default_path = value;
}

void CoreLib::loadConfig()
{

    QString path = getDefaultPath()->toHtmlEscaped()+QDir::separator()+"config.json";
    QFile jsonFile(path);
    if(jsonFile.exists()){
        jsonFile.open(QFile::ReadOnly);
        QByteArray data = jsonFile.readAll();
        QJsonDocument doc = QJsonDocument().fromJson(data);
        this->config = doc.object().toVariantMap();
        qDebug()<<"config = "<<config<<" "<<config.contains("about")<<config.value("emr-host");
        jsonFile.close();
    }else{
//        this->config = QVariantMap;
        config.insert("about","Soup v1.0");

        saveConfig();
    }



}

void CoreLib::saveConfig()
{

        QString path = getDefaultPath()->toHtmlEscaped()+QDir::separator()+"config.json";

        QJsonObject object = QJsonObject::fromVariantMap(config);
        QJsonDocument doc;
        doc.setObject(object);

        QFile jsonFile(path);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(doc.toJson());
        jsonFile.close();

        //    qDebug()<<"Write to file";
}

void CoreLib::setValue(QString key, QVariant value)
{
    config.insert(key,value);
}

QVariant CoreLib::getValue(QString key)
{
    return config.value(key);
}

QString CoreLib::getStringValue(QString key)
{
    return config.value(key).toString();
}

bool CoreLib::has(QString key)
{
    return config.contains(key);
}
void CoreLib::log(QString msg)
{
    QDateTime now = QDateTime::currentDateTime();
    QString stamp =  now.toString("hh:mm:ss");
    LogText *log = new LogText();
    log->msg = ""+stamp+" : "+msg;
    log->stamp = now;
    this->logs.push_front(log);

}

QString CoreLib::getLogText()
{
   QString res;
    int msg = 5;

    QDateTime now = QDateTime::currentDateTime();


    for(int i=0;i<msg&&i<logs.size();i++){
        LogText *log = this->logs.at(i);
        res.append(log->msg+"<br/>");
        qint64 msec = log->stamp.msecsTo(now);

        if(msec>2000)logs.removeOne(log);
    }
    return res;

}

void CoreLib::pushJobQueue(JobQueue *job)
{
    this->queues->append(job);
}

void CoreLib::processQueue()
{
//    job->process();
    bool some_job=false;
    int count = 0;
    while(queues->size()>0){

        JobQueue *last = queues->front();
        queues->pop_front();
        last->process();
        delete last;
        some_job = true;
//        if(count>1){
//            if(this->capture_mode==3&&this->mode==MODE_CAPTURE&&sum_job){
//                WebPage * page = ui->mode_live_content->getCurrentWebPage();
//                page->runJavaScript("refresh_procedure()");
//                live_capture_scene->clear();
//                core->log("UI updating..");
//                count = 0;
//            }
//        }

        count+=1;


    }
//    refresh_procedure

//    ui->stage->setCurrentWidget(ui->mode_web_capture);
//    if(this->capture_mode==3&&this->mode==MODE_CAPTURE&&sum_job){
//        WebPage * page = ui->mode_live_content->getCurrentWebPage();
//        page->runJavaScript("refresh_procedure()");
//        live_capture_scene->clear();
//        core->log("UI updating..");
//    }


}

Session *CoreLib::getCurrentSession() const
{
    return current_session;
}

void CoreLib::setCurrentSession(Session *value)
{
    current_session = value;
}

bool CoreLib::hasCurrentSession()
{
    return current_session!=NULL;
}

void CoreLib::finishSession()
{
    this->current_session=NULL;
}
