#ifndef MONITOR_WIDGET_H
#define MONITOR_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "progressmeterwidget.h"

class MonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = nullptr);

    void setPercentValue(const float &value);
    void setTitle(const QString &text);
    void setTips(const QString &text);
    void setColor(const QColor &color);

private:
    QVBoxLayout *m_layout;
    ProgressMeterWidget *m_progress;
    QLabel *m_tipsLabel;
};

#endif // MONITOR_WIDGET_H
