#ifndef SESSION_H
#define SESSION_H
#include <QString>
#include <QUrl>
class Session
{
public:
    Session();

    void parseUrl(const QUrl&url);

    QString getpatientHn() const;
    void setpatientHn(const QString &value);

    QString getpatientName() const;
    void setPatient_name(const QString &value);

    QString getpatientGender() const;
    void setpatientGender(const QString &value);

    QString getpatientAge() const;
    void setpatientAge(const QString &value);

    QString getdocumentId() const;
    void setdocumentId(const QString &value);

    QString getdocumentName() const;
    void setdocumentName(const QString &value);

    QHash<QString,QString> getParams();

    QString getSsid() const;
    void setSsid(const QString &value);

    int getsessionDbId() const;
    void setsessionDbId(int value);

    QUrl getsnapUrl() const;
    void setsnapUrl(const QUrl &value);

    void init();

private:

    int session_db_id=0;

    QUrl snap_url;

    QString ssid;

    QString document_id;
    QString document_name;

    QString patient_hn;
    QString patient_name;
    QString patient_gender;
    QString patient_age;


};

#endif // SESSION_H
