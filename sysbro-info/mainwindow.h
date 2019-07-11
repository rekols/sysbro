#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include "leftsidebar.h"
#include "contentwidget.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LeftSideBar *m_leftSideBar;
    ContentWidget *m_contentWidget;
};

#endif // MAINWINDOW_H
