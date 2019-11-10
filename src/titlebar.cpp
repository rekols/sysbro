#include "titlebar.h"
#include "utils.h"
#include <QTabBar>
#include <QLabel>

#include <QPushButton>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QHBoxLayout)
{
    QPixmap iconPixmap = Utils::renderSVG(":/resources/sysbro.svg", QSize(30, 30));
    QLabel *iconLabel = new QLabel;
    iconLabel->setPixmap(iconPixmap);

//    QTabBar *tabbar = new QTabBar;
//    tabbar->setFocusPolicy(Qt::NoFocus);
//    tabbar->addTab(tr("Home"));
//    tabbar->addTab(tr("Cleaner"));
//    tabbar->addTab(tr("Speed up"));
//    tabbar->addTab(tr("Tools"));

    m_layout->setMargin(0);
    m_layout->addSpacing(11);
    m_layout->addWidget(iconLabel);
    m_layout->addSpacing(10);
//    m_layout->addWidget(tabbar);
    m_layout->addStretch();

    setLayout(m_layout);

    //    connect(tabbar, &QTabBar::currentChanged, this, &TitleBar::tabbarCurrentChanged);
}
