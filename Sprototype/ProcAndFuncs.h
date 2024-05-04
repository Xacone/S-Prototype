#ifndef PROCANDFUNCS_H
#define PROCANDFUNCS_H

#include <QProcess>
#include <QStringList>
#include <iostream>

class Process_Handler : public QProcess
{
    Q_OBJECT

private:
    QString starter;
    QString processName;
    QStringList args;
    bool isRunning = false;

public:
    Process_Handler() { }

public slots:

    void setStarter(QString s) { starter = s; }

    QString VERSION()
    {
        return QString(R"(
    Version 3 - Yazid
)"); }

    void WIN32_CMDPROCESS(QString proc)
    {
        this->start(proc);
        isRunning = true;
        connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(Output()));
        connect(this, SIGNAL(readyReadStandardError()), this, SLOT(sendError()));
        // connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(ProcessFinished(int, QProcess::ExitStatus)));
    }

    bool ProcessState() { return isRunning; }
    void ProcessFinished(int, QProcess::ExitStatus) { this->terminate(); this->kill(); emit SendOutput(starter); }

    void Output() { emit SendOutput(QString(this->readAllStandardOutput()).toUtf8()); }
    void sendError() { emit SendOutput(QString::fromLocal8Bit(this->readAllStandardError())); }

signals:
    void SendOutput(QString);

};


#endif // PROCANDFUNCS_H
