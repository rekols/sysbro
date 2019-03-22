#include "cleanerpage.h"
#include "utils.h"
#include "widgets/horizontalseparator.h"
#include "widgets/iconlabel.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSvgWidget>
#include <QLabel>

CleanerPage::CleanerPage(QWidget *parent)
    : QWidget(parent),
      m_scanButton(new QPushButton("扫描垃圾")),
      m_clearButton(new QPushButton("一键清理")),
      m_scannedWidget(new ScannedWidget),
      m_stackedLayout(new QStackedLayout),
      m_spinner(new DSpinner),
      m_tips2Label(new QLabel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QVBoxLayout *tipsLayout = new QVBoxLayout;

    QSvgWidget *cleanerIcon = new QSvgWidget(":/resources/cleaner.svg");
    QLabel *tips1Label = new QLabel("系统清理，释放磁盘空间");
    m_tips2Label->setText("支持以下分类的清理");

    cleanerIcon->setFixedSize(120, 120);

    tips1Label->setStyleSheet("QLabel { font-size: 30px; color: #454747; }");
    m_tips2Label->setStyleSheet("QLabel { font-size: 15px; color: #454747; }");
    m_scanButton->setFixedSize(150, 50);
    m_clearButton->setFixedSize(150, 50);

    m_scanButton->setFocusPolicy(Qt::NoFocus);
    m_clearButton->setFocusPolicy(Qt::NoFocus);

    tipsLayout->addWidget(tips1Label, 0, Qt::AlignBottom);
    tipsLayout->addWidget(m_tips2Label, 0, Qt::AlignTop);

    topLayout->addWidget(cleanerIcon);
    topLayout->addSpacing(25);
    topLayout->addLayout(tipsLayout);
    topLayout->addWidget(m_scanButton);
    topLayout->addWidget(m_clearButton);
    topLayout->setContentsMargins(30, 20, 30, 0);

    HorizontalSeparator *hsep = new HorizontalSeparator;
    hsep->setFixedWidth(700);

    layout->addLayout(topLayout);
    layout->addSpacing(30);
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
    cacheLabel->setTitle("应用缓存");
    cacheLabel->setIconPixmap(Utils::renderSVG(":/resources/app_cache.svg", QSize(64, 64)));

    IconLabel *logsLabel = new IconLabel;
    logsLabel->setTitle("应用日志");
    logsLabel->setIconPixmap(Utils::renderSVG(":/resources/app_logs.svg", QSize(64, 64)));

    IconLabel *crashLabel = new IconLabel;
    crashLabel->setTitle("崩溃报告");
    crashLabel->setIconPixmap(Utils::renderSVG(":/resources/crash.svg", QSize(64, 64)));

    IconLabel *packagesLabel = new IconLabel;
    packagesLabel->setTitle("软件包缓存");
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
    m_tips2Label->setText("正在扫描，请稍后...");
}

void CleanerPage::handleScanFinished(quint64 totalSize)
{
    m_tips2Label->setText(QString("扫描成功，本次共发现%1垃圾，您可以选择清理").arg(Utils::formatBytes(totalSize)));

    m_stackedLayout->setCurrentIndex(2);
    m_spinner->stop();

    m_scanButton->setEnabled(true);
    m_scanButton->setVisible(false);
    m_clearButton->setVisible(true);
}

void CleanerPage::handleClearFinished(quint64 totalSize)
{
    m_tips2Label->setText(QString("清理完成，本次共清理%1垃圾").arg(Utils::formatBytes(totalSize)));
    m_stackedLayout->setCurrentIndex(0);
    m_scanButton->setEnabled(true);
    m_scanButton->setVisible(true);
    m_clearButton->setVisible(false);
}
