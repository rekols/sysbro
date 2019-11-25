#include "utils.h"
#include <QRegularExpression>
#include <QStandardPaths>
#include <QApplication>
#include <QImageReader>
#include <QStorageInfo>
#include <QFileInfo>
#include <QProcess>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QDir>

#ifdef Q_OS_UNIX
#include <sys/utsname.h>
#endif

#include <memory>
#include <fstream>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

QString Utils::getFileContent(const QString &path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}

QPixmap Utils::renderSVG(const QString &path, const QSize &size)
{
    QImageReader reader;
    QPixmap pixmap;
    reader.setFileName(path);

    if (reader.canRead()) {
        const qreal ratio = qApp->devicePixelRatio();
        reader.setScaledSize(size * ratio);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(ratio);
    } else {
        pixmap.load(path);
    }

    return pixmap;
}

QString Utils::getUserName()
{
    std::string user_name = std::getenv("USER");

    if (user_name.empty()) {
        user_name = std::getenv("USERNAME");
    }

    return QString::fromStdString(user_name);
}

QString Utils::getPlatform()
{
    struct utsname u;
    QString kernelType;

    if (uname(&u) == 0) {
        kernelType = QString::fromLatin1(u.sysname);
    }

    return QString("%1 %2")
           .arg(kernelType)
           .arg(QSysInfo::currentCpuArchitecture());
}

QString Utils::getDistribution()
{
    return QSysInfo::prettyProductName();
}

QString Utils::getKernelVersion()
{
    struct utsname u;
    QString kernelVersion;

    if (uname(&u) == 0) {
        kernelVersion = QString::fromLatin1(u.release);
    }

    return kernelVersion;
}

QString Utils::getBootTime()
{
    QProcess *process = new QProcess;
    process->start("systemd-analyze");
    process->waitForFinished(-1);

    QString output = process->readLine();
    QRegularExpression reg("\\s=.*s");
    QRegularExpressionMatch match = reg.match(output);
    QString bootTime = match.captured(0).remove(" = ");

    if (QLocale::system().name() == "zh_CN") {
        bootTime = bootTime.replace("min", "分").replace("s", "秒");
    }

    return bootTime;
}

QString Utils::getDebianVersion()
{
    QFile file("/etc/debian_version");

    // e.g. "9.0"
    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}

void Utils::getCpuInfo(QString &cpuModel, QString &cpuCore)
{
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly);

    QString buffer = file.readAll();
    QStringList model_line = buffer.split("\n").filter(QRegularExpression("^model name"));
    QStringList core_line = buffer.split("\n");

    cpuModel = model_line.first().split(":").at(1);
    cpuCore = QString::number(core_line.filter(QRegularExpression("^processor")).count());

    file.close();
}

void Utils::getCpuTime(unsigned long long &workTime, unsigned long long &totalTime)
{
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);

    QString buffer = file.readAll();
    QStringList list = buffer.split("\n").filter(QRegularExpression("^cpu "));
    QString line = list.first();
    QStringList lines = line.trimmed().split(QRegularExpression("\\s+"));

    unsigned long long user = lines.at(1).toLong();
    unsigned long long nice = lines.at(2).toLong();
    unsigned long long system = lines.at(3).toLong();
    unsigned long long idle = lines.at(4).toLong();
    unsigned long long iowait = lines.at(5).toLong();
    unsigned long long irq = lines.at(6).toLong();
    unsigned long long softirq = lines.at(7).toLong();
    unsigned long long steal = lines.at(8).toLong();
    //unsigned long long guest = lines.at(9).toLong();
    //unsigned long long guestnice = lines.at(10).toLong();

    workTime = user + nice + system;
    totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    file.close();
}

void Utils::getMemoryInfo(QString &memory, float &percent)
{
    QFile file("/proc/meminfo");
    file.open(QIODevice::ReadOnly);

    QString buffer = file.readAll();
    QStringList lines = buffer.split("\n").filter(QRegularExpression("^MemTotal|^MemAvailable|^SwapTotal|^SwapFree"));
    QRegularExpression sep("\\s+");

    unsigned long long memTotal = lines.at(0).split(sep).at(1).toLong();
    unsigned long long memAvailable = lines.at(1).split(sep).at(1).toLong();
    // unsigned long long swapTotal = lines.at(2).split(sep).at(1).toLong();
    // unsigned long long swapFree = lines.at(3).split(sep).at(1).toLong();

    memory = QString("%1 / %2").arg(formatBytes((memTotal - memAvailable) * 1024)).arg(formatBytes(memTotal * 1024));
    percent = (memTotal - memAvailable) * 100.0 / memTotal;

    file.close();
}

void Utils::getDiskInfo(QString &disk, float &percent)
{
    QList<QStorageInfo> storageInfoList = QStorageInfo::mountedVolumes();

    long long totalSize = 0, totalFree = 0, totalUsed = 0;
    QStringList devices;

    for (const QStorageInfo &info : storageInfoList) {
        if (!devices.contains(info.device())) {
            totalSize += info.bytesTotal();
            totalFree += info.bytesFree();
            totalUsed += info.bytesTotal() - info.bytesFree();
            devices << info.device();
        }
    }

    disk = QString("%1 / %2").arg(formatBytes(totalSize - totalFree)).arg(formatBytes(totalSize));
    percent = totalUsed * 100.0 / totalSize;

//    QProcess *process = new QProcess;
//    process->start("df -Pl");
//    process->waitForFinished();

//    QString buffer = process->readAllStandardOutput();
//    QStringList result = buffer.trimmed().split(QChar('\n'));
//    long long size = 0, used = 0, free = 0;
//    long long totalSize = 0, totalFree = 0, totalUsed = 0;

//    process->kill();
//    process->close();

//    for (const QString &line : result.filter(QRegularExpression("^/"))) {
//        QStringList slist = line.split(QRegularExpression("\\s+"));
//        size = slist.at(1).toLong() << 10;
//        used = slist.at(2).toLong() << 10;
//        free = slist.at(3).toLong() << 10;

//        totalSize += size;
//        totalFree += free;
//        totalUsed += used;
//    }

//    disk = QString("%1 / %2").arg(formatBytes(totalSize - totalFree)).arg(formatBytes(totalSize));
//    percent = used * 100.0 / size;
}

void Utils::getNetworkBandWidth(unsigned long long &receiveBytes, unsigned long long &sendBytes)
{
    QFile file("/proc/net/dev");
    file.open(QIODevice::ReadOnly);

    file.readLine();
    file.readLine();

    QString buffer;
    receiveBytes = 0;
    sendBytes = 0;

    while ((buffer = file.readLine()) != nullptr) {
        QStringList lines = buffer.trimmed().split(QRegularExpression("\\s+"));

        if (lines.first() != "lo:") {
            receiveBytes += lines.at(1).toLong();
            sendBytes += lines.at(9).toLong();
        }
    }

    file.close();
}

double Utils::getCpuTemperature()
{
    // ref: https://www.embeddedarm.com/blog/reading-cpu-temperature-and-controlling-led-with-c-via-sysfs/
    //      https://github.com/torvalds/linux/blob/master/Documentation/hwmon/sysfs-interface.rst

    std::string val;
    std::string preparedTemp;
    double temperature;

    std::ifstream temperatureFile("/sys/class/thermal/thermal_zone0/temp");

    if (temperatureFile.is_open()) {
        // The temperature is stored in 5 digits.  The first two are degrees in C.  The rest are decimal precision.
        temperatureFile >> val;

        temperatureFile.close();

        preparedTemp = val.insert(2, 1, '.');
        temperature = std::stod(preparedTemp);

        return temperature;
    } else {
        return 0;
    }
}

QString Utils::formatBytes(unsigned long long bytes, bool space)
{
    if (bytes < 1024)
        return QString::number(bytes, 'r', 1) + (space ? " " : "") + "B";

    else if (bytes / 1024 < 1024)
        return QString::number(bytes / 1024.0, 'r', 1) + (space ? " " : "") + "KB";

    else if (bytes / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024.0 / 1024.0, 'r', 1) + (space ? " " : "") + "MB";

    else if (bytes / 1024 / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024.0 / 1024.0 / 1024.0, 'r', 1) + (space ? " " : "") + "GB";

    else if (bytes / 1024 / 1024 / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024.0 / 1024.0 / 1024.0 / 1024.0, 'r', 1) + (space ? " " : "") + "TB";

    return QString("");
}

quint64 Utils::getFileSize(const QString &path)
{
    quint64 totalSize = 0;

    QFileInfo info(path);

    if (info.exists()) {
        if (info.isFile()) {
            totalSize += info.size();
        }else if (info.isDir()) {
            QDir dir(path);

            for (const QFileInfo &i : dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs)) {
                totalSize += getFileSize(i.absoluteFilePath());
            }
        }
    }

    return totalSize;
}

QFileInfoList Utils::getDpkgPackages()
{
    QDir reports("/var/cache/apt/archives");

    return reports.entryInfoList(QDir::Files);
}

QFileInfoList Utils::getCrashReports()
{
    QDir reports("/var/crash");

    return reports.entryInfoList(QDir::Files);
}

QFileInfoList Utils::getAppLogs()
{
    QDir logs("/var/log");

    return logs.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
}

QFileInfoList Utils::getAppCaches()
{
    QDir caches(getHomePath() + "/.cache");

    return caches.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
}

QString Utils::getHomePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

QString exec(const QString &cmd, QStringList args)
{
    std::unique_ptr<QProcess> process(new QProcess);

    if (args.isEmpty())
        process->start(cmd);
    else
        process->start(cmd, args);

    process->waitForFinished(-1);
    QString out = process->readAllStandardOutput();
    QString error = process->errorString();

    process->kill();
    process->close();

    if (process->error() != QProcess::UnknownError)
        throw error;

    return out.trimmed();
}

QString Utils::sudoExec(const QString &cmd, QStringList args)
{
    args.push_front(cmd);

    QString result("");

    try {
        result = exec("pkexec", args);
    } catch (QString &ex) {
        qCritical() << ex;
    }

    return result;
}

QList<int> Utils::getTaskPIDList()
{
    QProcess *process = new QProcess;
    process->start("ps", QStringList() << "ax" << "-weo" << "pid" << "--no-headings");
    process->waitForFinished(-1);

    QString content = process->readAllStandardOutput();
    QStringList splitList = content.split(QChar('\n'));
    QList<int> pidList;

    for (QString line : splitList) {
        line = line.trimmed();

        if (!line.isEmpty()) {
            pidList << line.toInt();
        }
    }

    return pidList;
}
