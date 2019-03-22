#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QApplication>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon(QObject *parent = nullptr);
    ~TrayIcon();

signals:
    void exitActionTriggered();
    void openActionTriggered();

private slots:
    void iconActive(QSystemTrayIcon::ActivationReason reason);

private:
    QMenu *m_menu;
    QAction *m_openAction;
    QAction *m_exitAction;
};

#endif
