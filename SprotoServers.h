#ifndef SPROTOSERVERS_H
#define SPROTOSERVERS_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <Strings.h>
#include <QCryptographicHash>
#include "pcap.h"
#include <QWidget>
#include "InitStats.h"
#include "QVBoxLayout"
#include <QTabWidget>
#include <QPushButton>
#include <QGroupBox>

class S_THREAD_CO : public QThread
{
    Q_OBJECT

private:
    QTcpSocket* qtcpsock;
    int INDEX;

public:

    S_THREAD_CO(QTcpSocket* in_sock, int i) : qtcpsock(in_sock), INDEX(i) {
        connect(in_sock, SIGNAL(readyRead()), this, SLOT(send_read()));
    }

    void run() override {}

    const QTcpSocket* getsock() { return qtcpsock; }

signals:
    void here_is_read_data(QByteArray, int);

public slots:
    void send_read() { emit here_is_read_data(qtcpsock->readAll(), INDEX); }
    void write_data(QByteArray req) { qtcpsock->write(req);
                                      //qtcpsock->waitForBytesWritten(3000);
    }

};

class _WIN_AGENT_ : public QWidget // AGENT WINDOWS
{
    Q_OBJECT

private:

    TabWidget *TB = new TabWidget();
    QVBoxLayout *qhb = new QVBoxLayout();

    QWidget *_AG_ACTIONS_ = new QWidget();
    QGroupBox *group_b = new QGroupBox();
    QVBoxLayout *gb_qvl = new QVBoxLayout();
        QPushButton *lock = new QPushButton("Vérouiller");
        QPushButton *shut = new QPushButton("Eteindre");
        QPushButton *rest = new QPushButton("Redémarrer");

    QWidget *_AG_STATS_ = new QWidget();
    QWidget *_AG_CONSOLE_ = new QWidget();
    QWidget *_AG_ACTIVITY_ = new QWidget();
    QWidget *_AG_NETWORK_ = new QWidget();

        QGridLayout *QGL = new QGridLayout();

            S_THREAD_CO* _STC_;

public:
    _WIN_AGENT_(S_THREAD_CO* STC) : _STC_(STC) {
        this->setLayout(qhb);

        QFont f = TB->font();

        f.setPixelSize(11);
        TB->setFont(f);

        group_b->setLayout(gb_qvl);
            gb_qvl->addWidget(lock);
            gb_qvl->addWidget(shut);
            gb_qvl->addWidget(rest);

        qhb->addWidget(TB);

        _AG_ACTIONS_->setLayout(QGL);
        QGL->addWidget(group_b);

        TB->addTab(_AG_ACTIONS_, "Actions");
        TB->addTab(_AG_STATS_, "Statistiques");
        TB->addTab(_AG_CONSOLE_, "Console");
        TB->addTab(_AG_ACTIVITY_, "Activité");
        TB->addTab(_AG_NETWORK_, "Réseau");

        connect(lock, SIGNAL(clicked()), this, SLOT(siglock()));
    }

    ~_WIN_AGENT_()
    {
        delete TB;
        delete qhb;
        delete lock;
    }

public slots:
    void siglock() { _STC_->write_data("SIGLOCK"); }
    void sigshut() { _STC_->write_data("SIGSHUT"); }
    void sigrest() { _STC_->write_data("SIGREST"); }

};

/*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

class TCP_SRV : public QThread
{
    Q_OBJECT
protected:

    QList<QHostAddress> HOSTS_ADDR;
    QTcpServer *_SRV_;
    QTcpSocket *_SC_;
    QList<S_THREAD_CO*> STC_LST;
    int port;
    int SOCK_NBR = 0;

public:

    TCP_SRV(int prt) : QThread(), port(prt)
    {
        _SRV_ = new QTcpServer;
        _SC_ = new QTcpSocket;

        connect(_SRV_, SIGNAL(newConnection()), this, SLOT(newConnection()));

        if(!_SRV_->listen(QHostAddress::Any, port))
        {
            qDebug() << "SPrototype server on " << port << " - startup failed" << endl;
        } else {
            qDebug() << "SPrototype server on " << port << " - startup succeed" << endl;
        }
    }

    S_THREAD_CO* get_S_THREAD_CO(int index)
    {
        return STC_LST[index];
    }

public slots:

     void newConnection()
     {
         _SC_ = _SRV_->nextPendingConnection();
         S_THREAD_CO *STC = new S_THREAD_CO(_SC_, SOCK_NBR);
         SOCK_NBR+=1;
         STC_LST.append(STC);
         HOSTS_ADDR.append(_SC_->peerAddress());
         std::cout << "Nouvelle connexion sur " << _SC_->peerPort() << std::endl;
         connect(STC, SIGNAL(here_is_read_data(QByteArray, int)), this, SLOT(read(QByteArray, int)));
         STC->start();
     }

     virtual void read(QByteArray, int)=0;
};

/*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


class CAP_SRV : public TCP_SRV
{
    Q_OBJECT
public:
    CAP_SRV(int p) : TCP_SRV(p) {}

signals:
    void here_is_retrived_packet(const u_char*);
    void CAP_STATE(bool);

public slots:
    void read(QByteArray data, int index) override {
       this->thread()->usleep(10);
       emit here_is_retrived_packet((const u_char*)qUncompress(data).data());
    }
};

/*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

class DATA_CONTROL_SRV : public TCP_SRV
{
    Q_OBJECT
private:

    //QList<QList<QByteArray>> MSGS;

public:
    DATA_CONTROL_SRV(int p) : TCP_SRV(p) {}
    QHostAddress get_addr(int i) { return HOSTS_ADDR[i]; }

signals:
    void IDENTITY_BRR(QString);

public slots:

    void read(QByteArray data, int index) override {

        if(data.contains("HELLO SERVER"))
        {
            STC_LST.at(index)->write_data("IDENTITY REQUEST");
        } else {
            if(data.contains("name: "))
            {
                emit IDENTITY_BRR(data.mid(6, data.size()) + "\n" + STC_LST.at(index)->getsock()->peerAddress().toString());
            }
        }

        //qDebug() << "!!-" << data << "\n";
    }
};


#endif // SPROTOSERVERS_H
