#ifndef DETECTIONENGINE_H
#define DETECTIONENGINE_H
#include <QThread>

class DetectionEngine : public QThread
{
    Q_OBJECT
private:

public:
    inline void run() override
    {
        while(true)
        {

            this->thread()->usleep(10);
        }
    }

signals:


};

#endif // DETECTIONENGINE_H
