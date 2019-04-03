#include "mainwindow.h"
#include "dtitlebar.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_titleBar(new TitleBar),
      m_stackedLayout(new QStackedLayout),
      m_homePage(new HomePage),
      m_cleanerPage(new CleanerPage),
      m_speedUpPage(new SpeedupPage),
      m_toolsPage(new ToolsPage),
      m_trayIcon(new TrayIcon),
      m_settings(new QSettings("sysbro")),
      m_trayIconAction(new QAction(tr("Display tray icon")))
{
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(m_stackedLayout);

    if (titlebar()) {
        titlebar()->setCustomWidget(m_titleBar, Qt::AlignVCenter, 0);
        titlebar()->setSeparatorVisible(true);
        titlebar()->setFixedHeight(43);

        QMenu *menu = new QMenu;
        menu->addAction(m_trayIconAction);
        menu->addSeparator();

        titlebar()->setMenu(menu);
    }

    // first start will start monitoring.
    m_homePage->startMonitor();

    m_stackedLayout->addWidget(m_homePage);
    m_stackedLayout->addWidget(m_cleanerPage);
    m_stackedLayout->addWidget(m_speedUpPage);
    m_stackedLayout->addWidget(m_toolsPage);

    m_trayIconAction->setCheckable(true);

    setWindowTitle("SysBro");
    setCentralWidget(centralWidget);
    setWindowRadius(16);
    setBorderColor(QColor("#BFBFBF"));
    setFixedSize(800, 560);
    initTrayIcon();
    // resize(800, 560);

    connect(m_trayIcon, &TrayIcon::openActionTriggered, this, &MainWindow::activeWindow);
    connect(m_trayIcon, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);
    connect(m_titleBar, &TitleBar::tabbarCurrentChanged, this, &MainWindow::handleTabbarCurrentChanged);
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

void MainWindow::handleTabbarCurrentChanged(int index)
{
    if (index == 0) {
        m_homePage->startMonitor();
    } else {
        m_homePage->stopMonitor();
    }

    m_stackedLayout->setCurrentIndex(index);
}
