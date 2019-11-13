#include "cleanerpage.h"
#include "utils.h"
#include "widgets/horizontalseparator.h"
#include "widgets/iconlabel.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

CleanerPage::CleanerPage(QWidget *parent)
    : QWidget(parent),
      m_scanButton(new QPushButton(tr("Scan now"))),
      m_clearButton(new QPushButton(tr("Clean up"))),
      m_scannedWidget(new ScannedWidget),
      m_stackedLayout(new QStackedLayout),
      m_spinner(new DSpinner),
      m_tips2Label(new QLabel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QVBoxLayout *tipsLayout = new QVBoxLayout;

    QPixmap cleanerPixmap = Utils::renderSVG(":/resources/cleaner.svg", QSize(80, 80));
    QLabel *cleanerIcon = new QLabel;
    cleanerIcon->setPixmap(cleanerPixmap);
    cleanerIcon->setFixedSize(80, 80);

    QLabel *tips1Label = new QLabel(tr("Clean up disk space"));
    m_tips2Label->setText(tr("Support scanning the following items"));

    tips1Label->setStyleSheet("QLabel { font-size: 30px; color: #454747; }");
    m_tips2Label->setStyleSheet("QLabel { font-size: 15px; color: #454747; }");
    m_scanButton->setFixedSize(150, 50);
    m_clearButton->setFixedSize(150, 50);

    m_scanButton->setFocusPolicy(Qt::NoFocus);
    m_clearButton->setFocusPolicy(Qt::NoFocus);

    tips1Label->setWordWrap(true);
    m_tips2Label->setWordWrap(true);

    tipsLayout->addWidget(tips1Label, 0, Qt::AlignBottom);
    tipsLayout->addWidget(m_tips2Label, 0, Qt::AlignTop);

    topLayout->addWidget(cleanerIcon);
    topLayout->addSpacing(20);
    topLayout->addLayout(tipsLayout);
    topLayout->addWidget(m_scanButton, 0, Qt::AlignTop);
    topLayout->addWidget(m_clearButton, 0, Qt::AlignTop);
    topLayout->setContentsMargins(30, 10, 30, 0);

    HorizontalSeparator *hsep = new HorizontalSeparator;
    hsep->setFixedWidth(700);

    layout->addLayout(topLayout);
    layout->addSpacing(20);
    layout->addWidget(hsep, 0, Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addLayout(m_stackedLayout);

    setLayout(layout);
    init();

    connect(m_scanButton, &QPushButton::clicked, this, &CleanerPage::handleScanBtnClicked);
    connect(m_clearButton, &QPushButton::clicked, m_scannedWidget, &ScannedWidget::clear);
    connect(m_scannedWidget, &ScannedWidget::scanFinished, this, &CleanerPage::handleScanFinished);
    connect(m_scannedWidget, &ScannedWidget::clearFinished, this, &CleanerPage::handleClearFinished);
}

void CleanerPage::init()
{
    QWidget *infoPage = new QWidget;
    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoPage->setLayout(infoLayout);

    IconLabel *cacheLabel = new IconLabel;
    cacheLabel->setTitle(tr("Application Caches"));
    cacheLabel->setIconPixmap(Utils::renderSVG(":/resources/app_cache.svg", QSize(64, 64)));

    IconLabel *logsLabel = new IconLabel;
    logsLabel->setTitle(tr("Application Logs"));
    logsLabel->setIconPixmap(Utils::renderSVG(":/resources/app_logs.svg", QSize(64, 64)));

    IconLabel *crashLabel = new IconLabel;
    crashLabel->setTitle(tr("Crash Reports"));
    crashLabel->setIconPixmap(Utils::renderSVG(":/resources/crash.svg", QSize(64, 64)));

    IconLabel *packagesLabel = new IconLabel;
    packagesLabel->setTitle(tr("Package Caches"));
    packagesLabel->setIconPixmap(Utils::renderSVG(":/resources/packages.svg", QSize(64, 64)));

    infoLayout->addWidget(cacheLabel);
    infoLayout->addWidget(logsLabel);
    infoLayout->addWidget(crashLabel);
    infoLayout->addWidget(packagesLabel);

    // loaddding bar.
    QWidget *spinnerPage = new QWidget;
    QVBoxLayout *spinnerLayout = new QVBoxLayout;
    spinnerPage->setLayout(spinnerLayout);
    spinnerLayout->addWidget(m_spinner, 0, Qt::AlignCenter);
    m_spinner->setFixedSize(50, 50);

    m_stackedLayout->addWidget(infoPage);
    m_stackedLayout->addWidget(spinnerPage);
    m_stackedLayout->addWidget(m_scannedWidget);

    m_scanButton->setVisible(true);
    m_clearButton->setVisible(false);
}

void CleanerPage::handleScanBtnClicked()
{
    m_stackedLayout->setCurrentIndex(1);
    m_spinner->start();
    m_scannedWidget->start();

    m_scanButton->setEnabled(false);
    m_tips2Label->setText(tr("Scanning, please wait..."));
}

void CleanerPage::handleClearBtnClicked()
{
    m_stackedLayout->setCurrentIndex(1);
    m_spinner->start();

    m_scannedWidget->clear();
    m_scanButton->setEnabled(false);
    m_clearButton->setEnabled(false);
}

void CleanerPage::handleScanFinished(quint64 totalSize)
{
    m_tips2Label->setText(QString(tr("Scan is successful, and a total of %1 files were found this time")).arg(Utils::formatBytes(totalSize)));

    m_stackedLayout->setCurrentIndex(2);
    m_spinner->stop();

    m_scanButton->setEnabled(true);
    m_clearButton->setEnabled(true);
    m_scanButton->setVisible(false);
    m_clearButton->setVisible(true);
}

void CleanerPage::handleClearFinished(quint64 totalSize)
{
    m_tips2Label->setText(tr("Clean up successfully, clean up a total of %1 files").arg(Utils::formatBytes(totalSize)));
    m_stackedLayout->setCurrentIndex(0);
    m_scanButton->setEnabled(true);
    m_scanButton->setVisible(true);
    m_clearButton->setVisible(false);
}
