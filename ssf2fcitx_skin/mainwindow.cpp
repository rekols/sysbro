#include "mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    mianWidget = new Widget;

    setCentralWidget(mianWidget);
    this->setWindowIcon(QIcon(QPixmap(":/icon/logo")));
    this->setWindowTitle("小盼皮肤转换器");

    //设置大小
    setMinimumSize(683, 344);
    setMaximumSize(683, 344);
}

MainWindow::~MainWindow()
{

}
