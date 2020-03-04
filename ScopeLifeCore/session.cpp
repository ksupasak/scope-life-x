#include "session.h"
#include <QUrlQuery>
Session::Session()
{

}

void Session::parseUrl(const QUrl &url)
{

    snap_url = url;


   QUrlQuery *query = new QUrlQuery(url);

   QString path = query->queryItemValue("path", QUrl::PrettyDecoded);
   QString p_id = query->queryItemValue("p_id", QUrl::PrettyDecoded);
   this->patient_hn = query->queryItemValue("ref", QUrl::PrettyDecoded);

   QStringList list = path.split("/");
   this->document_id = list.at(5).split("-").last();

   this->document_name = list.at(4);
   this->patient_name = query->queryItemValue("ref2", QUrl::PrettyDecoded);
//   if( this->patient_name==NULL){
//        this->patient_name =  this->patient_hn;
//   }


}

QString Session::getpatientHn() const
{
    return patient_hn;
}

void Session::setpatientHn(const QString &value)
{
    patient_hn = value;
}

QString Session::getpatientName() const
{
    return patient_name;
}

void Session::setPatient_name(const QString &value)
{
    patient_name = value;
}

QString Session::getpatientGender() const
{
    return patient_gender;
}

void Session::setpatientGender(const QString &value)
{
    patient_gender = value;
}

QString Session::getpatientAge() const
{
    return patient_age;
}

void Session::setpatientAge(const QString &value)
{
    patient_age = value;
}

QString Session::getdocumentId() const
{
    return document_id;
}

void Session::setdocumentId(const QString &value)
{
    document_id = value;
}

QString Session::getdocumentName() const
{
    return document_name;
}

void Session::setdocumentName(const QString &value)
{
    document_name = value;
}

QHash<QString, QString> Session::getParams()
{
    QHash<QString, QString> params;
    params["hn"] = this->patient_hn;
    params["id"] = this->document_id;
    params["doc_name"] = this->document_name;
    params["full_name"] = this->patient_name;
    params["ssid"] = this->ssid;
    return params;
}



QString Session::getSsid() const
{
    return ssid;
}

void Session::setSsid(const QString &value)
{
    ssid = value;
}

int Session::getsessionDbId() const
{
    return session_db_id;
}

void Session::setsessionDbId(int value)
{
    session_db_id = value;
}

QUrl Session::getsnapUrl() const
{
    return snap_url;
}

void Session::setsnapUrl(const QUrl &value)
{
    snap_url = value;
}

void Session::init()
{
    if(this->ssid!=NULL){
        QUrlQuery snap_query(this->snap_url);
        if(snap_query.hasQueryItem("ssid")){
            snap_query.removeQueryItem("ssid");
        }
        snap_query.addQueryItem("ssid",ssid);
        snap_url.setQuery(snap_query);
    }
}
