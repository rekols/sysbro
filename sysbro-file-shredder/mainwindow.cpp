#include "mainwindow.h"
#include "dtitlebar.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;

    if (titlebar()) {
        titlebar()->setBackgroundTransparent(true);
        titlebar()->setIcon(QIcon(":/images/icon.svg"));
        titlebar()->setTitle("");
        titlebar()->setStyleSheet(QString("%1"
                                          "Dtk--Widget--DTitlebar {"
                                          "background: #23AC38;"
                                          "}").arg(titlebar()->styleSheet()));
    }

    setWindowIcon(QIcon(":/images/icon.svg"));
    setCentralWidget(centralWidget);
    setWindowRadius(16);
    setWindowTitle("文件粉碎机");
    setFixedSize(800, 550);
}

MainWindow::~MainWindow()
{

}
