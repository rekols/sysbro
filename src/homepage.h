#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include "widgets/monitorwidget.h"
#include "monitorthread.h"

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

    void startMonitor();
    void stopMonitor();

private:
    void initUI();

private:
    void updateCpuPercent(float cpuPercent);
    void updateMemory(QString memory, float percent);
    void updateDisk(QString disk, float percent);
    void updateNetworkSpeed(QString upload, QString download);
    void updateNetworkTotal(QString upload, QString download);

private:
    QVBoxLayout *m_layout;
    MonitorWidget *m_cpuMonitorWidget;
    MonitorWidget *m_memoryMonitorWidget;
    MonitorWidget *m_diskMonitorWidget;
    MonitorThread *m_monitorThread;

    QLabel *m_systemInfo;
    QLabel *m_platform;
    QLabel *m_distribution;
    QLabel *m_bootTime;
    QLabel *m_kernel;
    QLabel *m_cpuModel;
    QLabel *m_cpuCoreCount;
    QLabel *m_uploadInfo;
    QLabel *m_downloadInfo;
    QLabel *m_uploadLabel;
    QLabel *m_downloadLabel;
};

#endif // HOMEPAGE_H
