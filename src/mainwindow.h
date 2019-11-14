#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include <QSettings>
#include "titlebar.h"
#include "home_page/homepage.h"
#include "cleanup_page/cleanerpage.h"
#include "speedup_page/speeduppage.h"
#include "tools_page/toolspage.h"
#include "widgets/trayicon.h"
#include "leftsidebar.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    // void paintEvent(QPaintEvent *event);

private:
    void initTrayIcon();
    void activeWindow();
    void handleLeftSideBarChanged(int index);

private:
    TitleBar *m_titleBar;
    LeftSideBar *m_leftSideBar;
    QStackedLayout *m_stackedLayout;
    HomePage *m_homePage;
    CleanerPage *m_cleanerPage;
    SpeedupPage *m_speedUpPage;
    ToolsPage *m_toolsPage;
    TrayIcon *m_trayIcon;
    QSettings *m_settings;
    QAction *m_trayIconAction;
};

#endif // MAINWINDOW_H
