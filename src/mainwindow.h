#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QStackedLayout>
#include <QSettings>
#include "titlebar.h"
#include "homepage.h"
#include "cleanerpage.h"
#include "speeduppage.h"
#include "toolspage.h"
#include "widgets/trayicon.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initTrayIcon();
    void activeWindow();
    void handleTabbarCurrentChanged(int index);

private:
    TitleBar *m_titleBar;
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
