#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <ddialog.h>
#include <QLineEdit>

DWIDGET_USE_NAMESPACE

class CreateWindow : public DDialog
{
    Q_OBJECT

public:
    explicit CreateWindow(QWidget *parent = nullptr);

    void setAppName(const QString &text);
    void setAppExec(const QString &text);
    void setAppIcon(const QString &text);

signals:
    void requestNewApp(const QString appName, const QString appIcon, const QString appExec);

private:
    void handleButtonClicked(const int index, const QString &text);

private:
    QLineEdit *m_appNameEdit;
    QLineEdit *m_appExecEdit;
    QLineEdit *m_appIconEdit;
};

#endif // CREATEWINDOW_H
