#ifndef MONITORTHREAD_H
#define MONITORTHREAD_H

#include <QThread>

class MonitorThread : public QThread
{
    Q_OBJECT

public:
    explicit MonitorThread(QObject *parent = nullptr);

    void run();

signals:
    void updateCpuPercent(float cpuPercent);
    void updateMemory(const QString memory, float percent);
    void updateDisk(const QString disk, float percent);
    void updateNetworkSpeed(const QString upload, const QString download);
    void updateNetworkTotal(const QString upload, const QString download);
    void updateProcessNumber(int num);
};

#endif // MONITORTHREAD_H
