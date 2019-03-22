#include "monitorthread.h"
#include "utils.h"

MonitorThread::MonitorThread(QObject *parent)
    : QThread(parent)
{

}

void MonitorThread::run()
{
    unsigned long long currentWorkTime = 0, prevWorkTime = 0;
    unsigned long long currentTotalTime = 0, prevTotalTime = 0;
    unsigned long long prevRecv = 0, prevSend = 0;
    unsigned long long recv = 0, send = 0;
    QString memory = "";
    QString disk = "";
    float memoryPercent = 0;
    float diskPercent = 0;

    while (1) {
        Utils::getMemoryInfo(memory, memoryPercent);
        Utils::getDiskInfo(disk, diskPercent);

        emit updateMemory(memory, memoryPercent);
        emit updateDisk(disk, diskPercent);

        Utils::getCpuTime(prevWorkTime, prevTotalTime);
        Utils::getNetworkBandWidth(prevRecv, prevSend);
        sleep(2);
        Utils::getCpuTime(currentWorkTime, currentTotalTime);
        Utils::getNetworkBandWidth(recv, send);

        emit updateNetworkTotal(Utils::formatBytes(send), Utils::formatBytes(recv));
        emit updateNetworkSpeed(Utils::formatBytes(send - prevSend), Utils::formatBytes(recv - prevRecv));
        emit updateCpuPercent((currentWorkTime - prevWorkTime) * 100.0 / (currentTotalTime - prevTotalTime));
    }
}
