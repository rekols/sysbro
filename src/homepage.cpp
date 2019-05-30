#include "homepage.h"
#include "utils.h"
#include "widgets/horizontalseparator.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_cpuMonitorWidget(new MonitorWidget),
      m_memoryMonitorWidget(new MonitorWidget),
      m_diskMonitorWidget(new MonitorWidget),
      m_monitorThread(new MonitorThread)
{   
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_cpuMonitorWidget);
    topLayout->addWidget(m_memoryMonitorWidget);
    topLayout->addWidget(m_diskMonitorWidget);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    QVBoxLayout *systemInfoLayout = new QVBoxLayout;
    QVBoxLayout *networkInfoLayout = new QVBoxLayout;

    m_systemInfo = new QLabel(tr("SYSTEM INFO"));
    m_platform = new QLabel;
    m_distribution = new QLabel;
    m_bootTime = new QLabel;
    m_kernel = new QLabel;
    m_cpuModel = new QLabel;
    m_cpuCoreCount = new QLabel;
    m_uploadInfo = new QLabel(tr("UPLOAD"));
    m_downloadInfo = new QLabel(tr("DOWNLOAD"));
    m_uploadLabel = new QLabel("0.0 B/s");
    m_downloadLabel = new QLabel("0.0 B/s");

    systemInfoLayout->addStretch();

    systemInfoLayout->addWidget(m_systemInfo);
    systemInfoLayout->addWidget(m_platform);
    systemInfoLayout->addWidget(m_distribution);
    systemInfoLayout->addWidget(m_bootTime);
    systemInfoLayout->addWidget(m_kernel);
    systemInfoLayout->addWidget(m_cpuModel);
    systemInfoLayout->addWidget(m_cpuCoreCount);
    systemInfoLayout->addStretch();

    // network layout.
    QLabel *networkIcon = new QLabel;
    QPixmap networkPixmap = Utils::renderSVG(":/resources/network.svg", QSize(16, 16));
    networkIcon->setFixedSize(16, 16);
    networkIcon->setPixmap(networkPixmap);

    QLabel *uploadIcon = new QLabel;
    QPixmap uploadPixmap = Utils::renderSVG(":/resources/upload.svg", QSize(16, 16));
    uploadIcon->setFixedSize(16, 16);
    uploadIcon->setPixmap(uploadPixmap);

    QLabel *downloadIcon = new QLabel;
    QPixmap downloadPixmap = Utils::renderSVG(":/resources/download.svg", QSize(16, 16));
    downloadIcon->setFixedSize(16, 16);
    downloadIcon->setPixmap(downloadPixmap);

    QHBoxLayout *uploadLayout = new QHBoxLayout;
    uploadLayout->addWidget(uploadIcon);
    uploadLayout->addWidget(m_uploadLabel);

    QHBoxLayout *downloadLayout = new QHBoxLayout;
    downloadLayout->addWidget(downloadIcon);
    downloadLayout->addWidget(m_downloadLabel);

    networkInfoLayout->addWidget(m_uploadInfo);
    networkInfoLayout->addLayout(uploadLayout);
    networkInfoLayout->addSpacing(20);
    networkInfoLayout->addWidget(m_downloadInfo);
    networkInfoLayout->addLayout(downloadLayout);
    networkInfoLayout->addStretch();

    bottomLayout->addSpacing(25);
    bottomLayout->addLayout(systemInfoLayout);
    bottomLayout->addSpacing(25);
    bottomLayout->addLayout(networkInfoLayout);
    bottomLayout->addSpacing(25);

    m_layout->addLayout(topLayout);
    m_layout->addStretch();
    m_layout->addWidget(new HorizontalSeparator);
    m_layout->addLayout(bottomLayout);
    m_layout->addStretch();

    initUI();
    setLayout(m_layout);

    connect(m_monitorThread, &MonitorThread::updateCpuPercent, this, &HomePage::updateCpuPercent);
    connect(m_monitorThread, &MonitorThread::updateMemory, this, &HomePage::updateMemory);
    connect(m_monitorThread, &MonitorThread::updateDisk, this, &HomePage::updateDisk);
    connect(m_monitorThread, &MonitorThread::updateNetworkSpeed, this, &HomePage::updateNetworkSpeed);
    connect(m_monitorThread, &MonitorThread::updateNetworkTotal, this, &HomePage::updateNetworkTotal);
}

void HomePage::startMonitor()
{
    m_monitorThread->start();
}

void HomePage::stopMonitor()
{
    // Don't update the data when switching to other pages.
    if (m_monitorThread->isRunning()) {
        m_monitorThread->terminate();
    }
}

void HomePage::initUI()
{
    QString strCpuModel("");
    QString strCpuCore("");
    Utils::getCpuInfo(strCpuModel, strCpuCore);

    m_platform->setText(tr("Platform: %1").arg(Utils::getPlatform()));
    m_distribution->setText(tr("Distribution: %1").arg(Utils::getDistribution()));
    m_bootTime->setText(tr("Startup time: %1").arg(Utils::getBootTime()));
    m_kernel->setText(tr("Kernal Release: %1").arg(Utils::getKernel()));
    m_cpuModel->setText(tr("CPU Model: %1").arg(strCpuModel));
    m_cpuCoreCount->setText(tr("CPU Core: %1").arg(strCpuCore));

    QFont font;
    font.setPointSize(18);
    m_systemInfo->setFont(font);
    m_uploadInfo->setFont(font);
    m_downloadInfo->setFont(font);

    m_systemInfo->setStyleSheet("QLabel { color: #4088C6 }");
    m_uploadInfo->setStyleSheet("QLabel { color: #31A38C }");
    m_downloadInfo->setStyleSheet("QLabel { color: #C45045 }");
    m_platform->setStyleSheet("QLabel { color: #505050 }");
    m_distribution->setStyleSheet("QLabel { color: #505050 }");
    m_kernel->setStyleSheet("QLabel { color: #505050 }");
    m_bootTime->setStyleSheet("QLabel { color: #505050 }");
    m_cpuModel->setStyleSheet("QLabel { color: #505050 }");
    m_cpuCoreCount->setStyleSheet("QLabel { color: #505050 }");
    m_uploadLabel->setStyleSheet("QLabel { color: #505050 }");
    m_downloadLabel->setStyleSheet("QLabel { color: #505050 }");

    // init monitor widgets.
    m_cpuMonitorWidget->setTitle("CPU");
    m_cpuMonitorWidget->setTips(tr("CPU Idle"));
    m_memoryMonitorWidget->setTitle(tr("MEMORY"));
    m_diskMonitorWidget->setTitle(tr("DISK"));

    m_memoryMonitorWidget->setColor("#18BD9B");
    m_diskMonitorWidget->setColor("#6F5BEC");
}

void HomePage::updateCpuPercent(float cpuPercent)
{
    m_cpuMonitorWidget->setPercentValue(cpuPercent);

    if (cpuPercent > 0 && cpuPercent < 50) {
        m_cpuMonitorWidget->setTips(tr("CPU Idle"));
    } else if (cpuPercent >= 50 && cpuPercent < 100) {
        m_cpuMonitorWidget->setTips(tr("CPU Busy"));
    }
}

void HomePage::updateMemory(QString memory, float percent)
{
    m_memoryMonitorWidget->setTips(memory);
    m_memoryMonitorWidget->setPercentValue(percent);
}

void HomePage::updateDisk(QString disk, float percent)
{
    m_diskMonitorWidget->setTips(disk);
    m_diskMonitorWidget->setPercentValue(percent);
}

void HomePage::updateNetworkSpeed(QString upload, QString download)
{
    m_uploadLabel->setText(upload + "/s");
    m_downloadLabel->setText(download + "/s");
}

void HomePage::updateNetworkTotal(QString upload, QString download)
{
    m_uploadInfo->setText(tr("UPLOAD") + QString(" (%1)").arg(upload));
    m_downloadInfo->setText(tr("DOWNLOAD") + QString(" (%1)").arg(download));
}

