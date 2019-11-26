#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>

class CpuInfo : public QObject
{
    Q_OBJECT

public:
    explicit CpuInfo(QObject *parent = 0);

    int getCpuCoreCount();
    QString getCpuVendor(int processorNumber);
    QString getCpuModel(int processorNumber);
    float getCurrentCpuSpeed(int processorNumber);
    QString getCpuInfoLine(int processorNumber, const QString &regExpStr);
    QString getInfoLine(const QString &regExpStr);

    long getCpuMaxMHz();
    long getCpuMinMHz();

private:
    QStringList m_lines;
    int m_cpuCoreCount;
};

#endif // CPUINFO_H
