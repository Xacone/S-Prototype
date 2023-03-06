#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

class DatabaseUtils : public QThread
{
protected:
    QSqlDatabase db;
    QSqlQuery *query;
    QStringList likeToList;
    QString likeTo;

public:
    virtual void Query(QString ip_addr)=0;
};

class IpGeoLoc : public DatabaseUtils
{
    Q_OBJECT

public:

    IpGeoLoc(QSqlDatabase &db) : DatabaseUtils() {
        query = new QSqlQuery(db);
    }

    virtual void Query(QString ip_addr)
    {
        likeToList = ip_addr.split(".");
        likeTo = "'" + likeToList.at(0) + "." + likeToList.at(1) + "." + likeToList.at(2) + ".0'";
        qDebug() << "Database state: " << likeTo;
        QString request = "SELECT code, region, lati, longi FROM ip_addrs WHERE start = " + likeTo;
        //qDebug() << request;
        query->exec(request);

        while(query->next())
        {
            qDebug() << query->value(1).toString();

            emit here_is_country_code(query->value(0).toString());
            emit here_is_lati_and_longi(query->value(1).toString(), query->value(2).toString(), query->value(3).toString());
        }
    }

signals:
    void here_is_lati_and_longi(QString, QString, QString);
    void here_is_region(QString);
    void here_is_country_code(QString);

};

#endif // DATABASEUTILS_H





