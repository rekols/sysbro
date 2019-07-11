#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include "overviewpage.h"

class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);

    void setCurrentIndex(int index);

private:
    QStackedLayout *m_layout;
    OverviewPage *m_overViewPage;
};

#endif // CONTENTWIDGET_H
