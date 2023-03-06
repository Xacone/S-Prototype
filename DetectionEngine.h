#ifndef DETECTIONENGINE_H
#define DETECTIONENGINE_H
#include <QThread>
#include <QStringList>
#include <QTime>
#include "CaptureThreads_FCTS.h"
#include "Headers.h"
#include <QDebug>
#include <iostream>
#include <QMutex>

class DetectionEngine : public QThread
{
    Q_OBJECT
private:
    QMutex *mut = new QMutex();
    QStringList* Tosend = new QStringList();
    QTime time;
    QDateTime dt;
    int index = 0;
    QStringList _DETAILS_;
    QString pack_to_hex;

    QString PDU_TO_HEX;

    QString Time;
    QString SRC_SENSOR;


public:

    DetectionEngine(){}
    ~DetectionEngine(){
        delete mut;
    }

    inline void run() override {}

    inline void init()
    {
        index+=1;
        Tosend->append(QString::number(index));
        Tosend->append(time.currentTime().toString());
    }

    inline int TCP_ANALYSIS(QString src, int sp, QString dst, int dp, tcp_hdr* tcph)
    {
        Time = time.currentTime().toString() + ":" + QString::number(time.currentTime().msec());

        // ------------ HEX ----------- //
            for(int i = 0 ; i < 20 ; i++) // A CORRIGER !!!
            {
                PDU_TO_HEX += char_tohex((u_char)(const u_char&)tcph[i]);
                i+=1;
                PDU_TO_HEX += char_tohex((u_char)(const u_char&)tcph[i]);
                PDU_TO_HEX += " ";
            }

            _DETAILS_.append(PDU_TO_HEX);
            PDU_TO_HEX = "";

        // 1. SCAN DE PORTS
        if((QString)get_tcp_flags_from_bin(tcph) == (QString)"FIN PSH URG] ")
        {
            // ---------------------- //

            mut->lock();
            init();

            // A factoriser !!
            Tosend->append("Warning");
            Tosend->append("Scan de ports");
            Tosend->append(src + ":" + QString::number(sp));
            Tosend->append(dst + ":" + QString::number(dp));
            Tosend->append("N/A");
            Tosend->append("TCP");
            Tosend->append("XMAS Scan");

            // Set ready to multiple sensors !!
            _DETAILS_.append(QString("<b>Date and time:</b> " + dt.currentDateTime().toString() + " " + Time));
            _DETAILS_.append(QString("<b>Source sensor:</b> " + QString("localhost")));
            _DETAILS_.append(QString("<b>Severity: </b>") + QString("Medium"));
            _DETAILS_.append(QString("<b>Type: </b>") + QString("Port scanning - TCP XMAS"));
            _DETAILS_.append(QString("<b>Followed rules: </b>") + QString("Embedded"));
            _DETAILS_.append("");
            _DETAILS_.append(QString("<b>Source: </b>") + QString(src));
            _DETAILS_.append(QString("<b>Tool fingerprint: </b>") + QString("Nmap"));
            _DETAILS_.append(QString("<b>OS fingerprint: </b>") + QString("Windows"));
            _DETAILS_.append(QString("<b>Country: </b>") + QString("France"));


            emit here_is_result(Tosend, _DETAILS_);

            this->usleep(1);
            mut->unlock();

        }

        _DETAILS_.clear();
        Tosend = new QStringList();

        return 0;
    }

signals:
    void here_is_result(QStringList*, QStringList); // Envoyer le QLIST ici

public slots:

};

#endif // DETECTIONENGINE_H
