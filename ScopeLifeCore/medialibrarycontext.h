#ifndef MEDIALIBRARYCONTEXT_H
#define MEDIALIBRARYCONTEXT_H

#include <QObject>
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "corelib.h"

class MediaLibraryContext

{

public:
    MediaLibraryContext(CoreLib *core);
    void checkSchema();
    QString generateInternalStoragePath(QString type);
    QString generateInternalStoragePath(QHash<QString,QString> data, QString type);
    QString replacePattern(QString pattern, QHash<QString, QString> lookup);

    QSqlDatabase *getDatabaseConnection();


    CoreLib *getCore() const;
    void setCore(CoreLib *value);

    QHash<QString, QString> getParams() const;
    void setParams(const QHash<QString, QString> &value);

protected:

    CoreLib *core;
    QSqlDatabase db;
    QString error;
    QHash<QString,QString> params;

};

#endif // MEDIALIBRARYCONTEXT_H
