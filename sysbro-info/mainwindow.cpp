#include "mainwindow.h"
#include "systeminfo.h"
#include <DTitlebar>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_leftSideBar(new LeftSideBar),
      m_contentWidget(new ContentWidget)
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_leftSideBar);
    layout->addWidget(m_contentWidget);

    if (titlebar()) {
        titlebar()->setIcon(QIcon(":/resources/logo.svg"));
        titlebar()->setSeparatorVisible(true);
        titlebar()->setTitle("");
    }

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowIcon(QIcon(":/resources/logo.svg"));
    resize(900, 600);

    connect(m_leftSideBar, &LeftSideBar::buttonClicked, m_contentWidget, &ContentWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{

}
