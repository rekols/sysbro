#include "titlebar.h"
#include <QTabBar>
#include <QSvgWidget>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QHBoxLayout)
{
    QSvgWidget *iconWidget = new QSvgWidget(":/resources/sysbro.svg");
    iconWidget->setFixedSize(22, 22);

    QTabBar *tabbar = new QTabBar;
    tabbar->setFocusPolicy(Qt::NoFocus);
    tabbar->addTab(tr("Home"));
    tabbar->addTab(tr("Cleaner"));
    tabbar->addTab(tr("Speed up"));
    tabbar->addTab(tr("Tools"));

    m_layout->setMargin(0);
    m_layout->addSpacing(10);
    m_layout->addWidget(iconWidget);
    m_layout->addSpacing(10);
    m_layout->addWidget(tabbar);
    m_layout->addStretch();

    setLayout(m_layout);

    connect(tabbar, &QTabBar::currentChanged, this, &TitleBar::tabbarCurrentChanged);
}
