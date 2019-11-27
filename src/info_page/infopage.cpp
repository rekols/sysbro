#include "infopage.h"
#include "widgets/roundedlabel.h"
#include "widgets/roundedwidget.h"
#include "systeminfo.h"
#include "utils.h"
#include <QScrollArea>
#include <QFormLayout>
#include <QPainter>
#include <QLabel>
#include <QTimer>

#include "infolabel.h"
#include "pciinfo.h"
#include "cpuinfo.h"

InfoPage::InfoPage(QWidget *parent)
    : QWidget(parent),
      m_contentLayout(new QVBoxLayout)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *contentWidget = new QWidget;

    contentWidget->setLayout(m_contentLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setContentsMargins(0, 0, 0, 0);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);
    scrollArea->setStyleSheet("QScrollArea {background-color: transparent;}");
    scrollArea->viewport()->setStyleSheet("background-color: transparent;");

    layout->setMargin(0);
    layout->addSpacing(30);
    layout->addWidget(scrollArea);
    layout->addSpacing(30);
    setLayout(layout);

    QTimer::singleShot(500, this, &InfoPage::initInfo);
}

void InfoPage::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F8F8F8"));
    painter.drawRect(rect());

    QRect rounded_rect = rect().marginsRemoved(QMargins(20, 20, 20, 20));
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRoundedRect(rounded_rect, 16, 16);
}

void InfoPage::initInfo()
{
    // productName, productFamily, productVersion
    QStringList productInfo = SystemInfo::getProductInfo();
    QString computerModel = QString("%1 %2").arg(productInfo.at(1)).arg(productInfo.at(0));
    QFormLayout *overviewLayout = new QFormLayout;
    overviewLayout->addRow(new InfoLabel(tr("Computer Model")), new InfoLabel(computerModel));
    overviewLayout->addRow(new InfoLabel(tr("Computer Type")), new InfoLabel(SystemInfo::getComputerType()));
    overviewLayout->addRow(new InfoLabel(tr("Host Name")), new InfoLabel(SystemInfo::getHostName()));
    overviewLayout->addRow(new InfoLabel(tr("User Name")), new InfoLabel(SystemInfo::getUserName()));
    overviewLayout->addRow(new InfoLabel(tr("Platform")), new InfoLabel(Utils::getPlatform()));
    overviewLayout->addRow(new InfoLabel(tr("Distribution")), new InfoLabel(SystemInfo::getDistribution()));
    overviewLayout->addRow(new InfoLabel(tr("Kernal Release")), new InfoLabel(Utils::getKernelVersion()));

    overviewLayout->setHorizontalSpacing(100);
    overviewLayout->setVerticalSpacing(7);
    overviewLayout->setMargin(0);

    // cpu info.
    CpuInfo cpuInfo;
    const int cpuCoreCount = cpuInfo.getCpuCoreCount();

    overviewLayout->addRow(" ", (QWidget *)nullptr);
    overviewLayout->addRow(new InfoLabel(tr("CPU Model")), new InfoLabel(cpuInfo.getCpuModel(0)));
    overviewLayout->addRow(new InfoLabel(tr("CPU Vendor")), new InfoLabel(cpuInfo.getCpuVendor(0)));
    overviewLayout->addRow(new InfoLabel(tr("CPU Core Count")), new InfoLabel(QString::number(cpuCoreCount)));
    overviewLayout->addRow(new InfoLabel(tr("CPU max MHz")), new InfoLabel(QString::number(cpuInfo.getCpuMaxMHz())));
    overviewLayout->addRow(new InfoLabel(tr("CPU min MHz")), new InfoLabel(QString::number(cpuInfo.getCpuMinMHz())));
    overviewLayout->addRow(" ", (QWidget *)nullptr);

    // ---------------------------

    PCIInfo pciInfo;
    for (PCIInfo::DeviceInfo &info : pciInfo.devices()) {
        overviewLayout->addRow(new InfoLabel(tr("Device Name")), new InfoLabel(info.name));
        overviewLayout->addRow(new InfoLabel(tr("Device Type")), new InfoLabel(info.className));
        overviewLayout->addRow(new InfoLabel(tr("Device Vendor")), new InfoLabel(info.vendor));
        overviewLayout->addRow(" ", (QWidget *)nullptr);
    }

    m_contentLayout->addLayout(overviewLayout);
    m_contentLayout->setContentsMargins(QMargins(40, 10, 40, 40));
}
