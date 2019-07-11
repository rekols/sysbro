#include "overviewpage.h"
#include "systeminfo.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QProcess>
#include <QLabel>
#include <QFile>

OverviewPage::OverviewPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel *productNameLabel = new QLabel;
    QLabel *productFamilyLabel = new QLabel;
    QLabel *productVersionLabel = new QLabel;
    QLabel *deviceTypeLabel = new QLabel;
    QLabel *kernelLabel = new QLabel;
    QLabel *hostNameLabel = new QLabel;
    QLabel *userNameLabel = new QLabel;
    QLabel *distributionLabel = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *contentWidget = new QWidget;
    QFormLayout *contentLayout = new QFormLayout;
    contentWidget->setLayout(contentLayout);

    contentLayout->addRow(new QLabel(tr("Product name")), productNameLabel);
    contentLayout->addRow(new QLabel(tr("Product family")), productFamilyLabel);
    contentLayout->addRow(new QLabel(tr("Product version")), productVersionLabel);
    contentLayout->addRow(new QLabel(tr("Device type")), deviceTypeLabel);
    contentLayout->addRow(new QLabel(tr("Host name")), hostNameLabel);
    contentLayout->addRow(new QLabel(tr("User name")), userNameLabel);
    contentLayout->addRow(new QLabel(tr("Distribution")), distributionLabel);
    contentLayout->addRow(new QLabel(tr("Kernel")), kernelLabel);
    contentLayout->setHorizontalSpacing(40);
    contentLayout->setVerticalSpacing(10);
    contentLayout->setLabelAlignment(Qt::AlignLeft);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setContentsMargins(0, 0, 0, 0);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);

    layout->addWidget(scrollArea);

    QStringList productInfoList = SystemInfo::getProductInfo();

    productNameLabel->setText(productInfoList.at(0));
    productFamilyLabel->setText(productInfoList.at(1));
    productVersionLabel->setText(productInfoList.at(2));
    deviceTypeLabel->setText(SystemInfo::getDeviceType());
    kernelLabel->setText(SystemInfo::getKernel());
    hostNameLabel->setText(SystemInfo::getHostName());
    userNameLabel->setText(SystemInfo::getUserName());
    distributionLabel->setText(SystemInfo::getDistribution());
}
