#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_currentIndex = 0;

    m_colorList << Qt::black << Qt::red << Qt::green << Qt::blue << QColor("#FFB400")
                << Qt::white << QColor("#808080");

    // Qt::X11BypassWindowManagerHint
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorList.at(m_currentIndex));
    painter.drawRect(rect());

    switch (m_currentIndex) {
    case 2: case 4: case 5:
        painter.setPen(Qt::black);
        break;
    default:
        painter.setPen(Qt::white);
        break;
    }

    const QRect textRect(rect().x(), rect().y() + 10, rect().width(), rect().height());
    // 纯色: 液晶显示器坏点检测(点击屏幕继续)
    painter.drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, tr("Solid color: LCD monitor dead pixel detection (click the screen to continue)"));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        if (m_currentIndex == m_colorList.size() - 1) {
            QMainWindow::close();
            return;
        }

        m_currentIndex += 1;
        QMainWindow::update();
    }
}
