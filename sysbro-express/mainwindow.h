#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>

class QNetworkAccessManager;
class QNetworkReply;

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QNetworkAccessManager *http;

    QWidget *mainWidget;
    QVBoxLayout *layout;
    QHBoxLayout *topLayout;
    QHBoxLayout *contentLayout;
    QComboBox *comboBox;
    QLineEdit *numberEdit;
    QPushButton *searchButton;
    QPlainTextEdit *contentBox;

    void initComboBoxItem();
    void query();
    void replyFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
