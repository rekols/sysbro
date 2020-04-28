#include "mainwindow.h"
#include "dtitlebar.h"
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_titleBar(new TitleBar),
      m_leftSideBar(new LeftSideBar),
      m_stackedLayout(new QStackedLayout),
      m_homePage(new HomePage),
      m_infoPage(new InfoPage),
      m_cleanerPage(new CleanerPage),
      m_speedUpPage(new SpeedupPage),
      m_toolsPage(new ToolsPage),
      m_trayIcon(new TrayIcon),
      m_settings(new QSettings("sysbro")),
      m_trayIconAction(new QAction(tr("Display tray icon"), this))
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_leftSideBar);
    mainLayout->addLayout(m_stackedLayout);

    centralWidget->setLayout(mainLayout);

    if (titlebar()) {
        titlebar()->setCustomWidget(m_titleBar, false);
        titlebar()->setSeparatorVisible(false);
        titlebar()->setSwitchThemeMenuVisible(false);

        QMenu *menu = new QMenu;
        menu->addAction(m_trayIconAction);
        menu->addSeparator();

        titlebar()->setMenu(menu);
    }

    // first start will start monitoring.
    m_homePage->startMonitor();

    m_stackedLayout->addWidget(m_homePage);
    m_stackedLayout->addWidget(m_infoPage);
    m_stackedLayout->addWidget(m_cleanerPage);
    m_stackedLayout->addWidget(m_speedUpPage);
    m_stackedLayout->addWidget(m_toolsPage);

    m_trayIconAction->setCheckable(true);

    setWindowTitle("Sysbro");
    setCentralWidget(centralWidget);
    setBorderColor(QColor("#C3C3C3"));
    setFixedSize(820, 550);
    initTrayIcon();
    // setMinimumSize(800, 560);
    // resize(800, 560);

    connect(m_trayIcon, &TrayIcon::openActionTriggered, this, &MainWindow::activeWindow);
    connect(m_trayIcon, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);
    connect(m_leftSideBar, &LeftSideBar::buttonClicked, this, &MainWindow::handleLeftSideBarChanged);
    connect(m_trayIconAction, &QAction::triggered, this, [=] {
        bool enabled = !m_settings->value("tray_icon").toBool();
        m_settings->setValue("tray_icon", enabled);
        initTrayIcon();
    });
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_settings->value("tray_icon").toBool()) {
        setVisible(false);
        event->ignore();
    } else {
        event->accept();
    }
}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);

//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor("#FFFFFF"));

//    const QRect titlebarRect = QRect(0, 0, rect().width(), titlebar()->height());
//    painter.drawRect(titlebarRect);

//    const QRect rect1 = QRect(0, titlebar()->height() + 1, rect().width(), 1);
//    painter.setBrush(QColor("#F1F1F1"));
//    painter.drawRect(rect1);

//    const QRect rect2 = QRect(0, titlebar()->height() + 2, rect().width(), 1);
//    painter.setBrush(QColor("#F5F5F5"));
//    painter.drawRect(rect2);

//    const QRect bgRect = QRect(0, titlebar()->height() + 3, rect().width(), rect().height());
//    painter.setBrush(QColor("#FAFAFA"));
//    painter.drawRect(bgRect);
//}

void MainWindow::initTrayIcon()
{
    if (m_settings->value("tray_icon").toBool()) {
        m_trayIconAction->setChecked(true);
        m_trayIcon->show();
    } else {
        // ubuntu 18.10 is invalid.
        m_trayIconAction->setChecked(false);
        m_trayIcon->hide();
    }
}

void MainWindow::activeWindow()
{
    setVisible(!isVisible());

    if (isVisible()) {
        DMainWindow::activateWindow();
    }
}

void MainWindow::handleLeftSideBarChanged(int index)
{
    if (index == 0) {
        m_homePage->startMonitor();
    } else {
        m_homePage->stopMonitor();
    }

    m_stackedLayout->setCurrentIndex(index);
}
