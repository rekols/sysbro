#include "infopage.h"
#include "widgets/roundedlabel.h"
#include "systeminfo.h"
#include "utils.h"
#include <QScrollArea>
#include <QLabel>

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

    layout->addWidget(scrollArea);
    setLayout(layout);
    initInfo();
}

void InfoPage::initInfo()
{
    // productName, productFamily, productVersion
    QStringList productInfo = SystemInfo::getProductInfo();
    QString computerModel = QString("%1 %2").arg(productInfo.at(1)).arg(productInfo.at(0));

    RoundedLabel *modelLabel = new RoundedLabel(tr("Computer Model"), computerModel);
    RoundedLabel *deviceType = new RoundedLabel(tr("Device Type"), SystemInfo::getDeviceType());
    RoundedLabel *hostName = new RoundedLabel(tr("Host Name"), SystemInfo::getHostName());
    RoundedLabel *userName = new RoundedLabel(tr("User Name"), SystemInfo::getUserName());
    RoundedLabel *platformLabel = new RoundedLabel(tr("Platform"), Utils::getPlatform());
    RoundedLabel *distrLabel = new RoundedLabel(tr("Distribution"), SystemInfo::getDistribution());
    RoundedLabel *kernelLabel = new RoundedLabel(tr("Kernal Release"), Utils::getKernelVersion());

    m_contentLayout->addWidget(modelLabel);
    m_contentLayout->addWidget(deviceType);
    m_contentLayout->addWidget(hostName);
    m_contentLayout->addWidget(userName);
    m_contentLayout->addWidget(platformLabel);
    m_contentLayout->addWidget(distrLabel);
    m_contentLayout->addWidget(kernelLabel);
    m_contentLayout->addStretch();
}
