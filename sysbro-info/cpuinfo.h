#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>

class CpuInfo : public QObject
{
    Q_OBJECT

public:
    explicit CpuInfo(QObject *parent = 0);
};

#endif // CPUINFO_H
