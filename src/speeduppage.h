#ifndef SPEEDUPPAGE_H
#define SPEEDUPPAGE_H

#include <QWidget>
#include <QLabel>
#include "serviceview.h"
#include "servicemodel.h"

class SpeedupPage : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedupPage(QWidget *parent = nullptr);

    void setItemsNumber(int number);

private:
    QLabel *m_tipsLabel;
    ServiceView *m_listView;
    ServiceModel *m_model;
};

#endif // SPEEDUPPAGE_H
