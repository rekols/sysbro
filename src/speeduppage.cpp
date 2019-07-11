#include "serviceitemdelegate.h"
#include "speeduppage.h"
#include "utils.h"
#include <QVBoxLayout>
#include <QLabel>

SpeedupPage::SpeedupPage(QWidget *parent)
    : QWidget(parent),
      m_tipsLabel(new QLabel),
      m_listView(new ServiceView),
      m_model(new ServiceModel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QVBoxLayout *infoLayout = new QVBoxLayout;

    QLabel *iconLabel = new QLabel;
    iconLabel->setPixmap(Utils::renderSVG(":/resources/speedup.svg", QSize(80, 80)));

    QLabel *bottomLabel = new QLabel(tr("Turn off unnecessary startup services can enhance boot spped"));
    m_tipsLabel->setStyleSheet("QLabel { color: #666666; font-size: 30px; }");
    bottomLabel->setStyleSheet("QLabel { color: #666666; }");

    infoLayout->addWidget(m_tipsLabel);
    infoLayout->addWidget(bottomLabel, 0, Qt::AlignTop);

    topLayout->addSpacing(10);
    topLayout->addWidget(iconLabel, 0, Qt::AlignTop);
    topLayout->addSpacing(20);
    topLayout->addLayout(infoLayout);
    topLayout->addStretch();

    layout->setContentsMargins(30, 20, 30, 0);
    layout->addLayout(topLayout);
    layout->addSpacing(20);
    layout->addWidget(m_listView);
    layout->addSpacing(20);

    m_listView->setModel(m_model);
    m_listView->setItemDelegate(new ServiceItemDelegate);
    setItemsNumber(0);

    setLayout(layout);

    connect(m_model, &ServiceModel::requestServicesNumber, this, &SpeedupPage::setItemsNumber);
    connect(m_listView, &ServiceView::switchActionTriggered, this, [=] (QModelIndex index) {
        m_model->switchStatus(index);
    });
}

void SpeedupPage::setItemsNumber(int number)
{
    m_tipsLabel->setText(QString(tr("Your computer has %1 startup items")).arg(number));
}
