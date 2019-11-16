#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QLabel>
#include "listview.h"
#include "listmodel.h"
#include "autostartmanager.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void handleNewApp(const QString appName, const QString appExec);
    void popupRightMenu(QModelIndex idx);
    void popupCreateWindow();
    void popupEditDialog(QModelIndex idx);
    void popupFileDialog();
    void checkAutoStartApp();
    void deleteAllApps();

private:
    QLabel *m_tipsLabel;
    ListModel *m_listModel;
    ListView *m_listView;
    AutoStartManager *m_autoStartManager;
};

#endif // MAINWINDOW_H
