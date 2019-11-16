#ifndef MONITOR_WIDGET_H
#define MONITOR_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVariantAnimation>
#include <QLabel>
#include "../widgets/progressbar.h"
#include "../widgets/roundedwidget.h"

class MonitorWidget : public RoundedWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = nullptr);

    void setPercentValue(const float &value);
    void setTitle(const QString &text);
    void setTips(const QString &text);
    void setColor(const QColor &color);
    void setIcon(const QString &iconPath, const QSize &size);

private:
    QVBoxLayout *m_layout;
    // QVariantAnimation *m_progressAnimation;
    // ProgressBar *m_progress;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_percentLabel;
    QLabel *m_tipsLabel;
};

#endif // MONITOR_WIDGET_H
