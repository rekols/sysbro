#include "mainwindow.h"
#include "dtitlebar.h"
#include <QVBoxLayout>

#include <QIODevice>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_stackedLayout(new QStackedLayout),
      m_homePage(new HomePage)
{
    QWidget *centralWidget = new QWidget;
    m_stackedLayout->addWidget(m_homePage);
    centralWidget->setLayout(m_stackedLayout);

    if (titlebar()) {
        titlebar()->setBackgroundTransparent(true);
        titlebar()->setIcon(QIcon(":/images/icon.svg"));
        titlebar()->setTitle("");
    }

    setWindowIcon(QIcon(":/images/icon.svg"));
    setCentralWidget(centralWidget);
    setWindowRadius(16);
    setWindowTitle("网络测速");
    setFixedSize(500, 420);

    QNetworkRequest request(QUrl("http://dlied6.qq.com/invc/xfspeed/qqpcmgr/download/Test216MB.dat"));
}

MainWindow::~MainWindow()
{

}
