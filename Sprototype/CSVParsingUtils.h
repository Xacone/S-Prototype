#ifndef CSVPARSINGUTILS_H
#define CSVPARSINGUTILS_H

#include <QThread>
#include <QDebug>
#include "CsvUtils.h"
#include <stack>


// /!\ Changement radical à venir -> tout drop sur serveur tiers, 512Mo /!\

class ParsingUtils_IPGeoLoc : public QThread
{
       Q_OBJECT

private:

    std::string file;
    std::stack<QString> _IP_ADDR_STACK_;

    std::string ipR_start;
    std::string ipR_end;
    std::string code;
    float lati;
    float longi;

    /* ---------- CURR VARS ---------- */
    QString curr_requested;

    QString curr_code;
    QString curr_lati;
    QString curr_longi;

    /* ---------- CURR RESULT ---------- */
    QStringList curr_result;

    /* ---------- SPLITED ---------- */
    QStringList targeted_sp;
    QStringList ipR_start_sp;
    QStringList ipR_end_sp;

    /* ---------- HISTORIQUE (STATIQUE !) ---------- */
    static QList<QStringList> History;

public:

    ParsingUtils_IPGeoLoc(std::string f) : file(f) {}

    inline void run() override
    {
        /*
        // A OPTIMISER !!!!!!

        qDebug() << "wsh \n";

       // this->exit();

        io::CSVReader<5> in(file);
        in.read_header(io::ignore_extra_column, "start", "end", "code", "lati", "longi");

        while(in.read_row(ipR_start, ipR_end, code, lati, longi))
        {
            ipR_start_sp = QString::fromStdString(ipR_start).split(".");
            ipR_end_sp = QString::fromStdString(ipR_end).split(".");

            if((targeted_sp.at(0).toInt() == ipR_start_sp.at(0).toInt()) &&
               (targeted_sp.at(1).toInt() == ipR_start_sp.at(1).toInt()) &&
               (targeted_sp.at(2).toInt() >= ipR_start_sp.at(2).toInt()) &&
               (targeted_sp.at(2).toInt() <= ipR_end_sp.at(2).toInt()) &&
               (targeted_sp.at(3).toInt() >= ipR_start_sp.at(3).toInt()) &&
               (targeted_sp.at(3).toInt() <= ipR_end_sp.at(3).toInt()))
            {
                qDebug() << "fait 2";
                curr_result.append(QString::fromStdString(ipR_start));
                curr_result.append(QString::fromStdString(ipR_end));
                curr_result.append(QString::fromStdString(code));
                curr_result.append(QString::number(lati));
                curr_result.append(QString::number(longi));

                qDebug() << "Resultat: " << curr_result << "\n";
                curr_result.clear();

                emit isFinished();
                break;
            }
            emit isRunning();
        }

        */
        return;
    }

public slots:

    QStringList GetIp4Info(QString ip_addr)
    {
        _IP_ADDR_STACK_.push(ip_addr);

        curr_requested = ip_addr;
        targeted_sp = curr_requested.split(".");
        this->start();

        this->quit();
        return curr_result;

    }

signals:
    void here_is_localisation(QStringList);

};



#endif // CSVPARSINGUTILS_H
