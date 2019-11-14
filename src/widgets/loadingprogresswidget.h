#ifndef LOADINGPROGRESSWIDGET_H
#define LOADINGPROGRESSWIDGET_H

#include <QTimer>
#include <QWidget>

struct Position
{
    double x;
    double y;
};

/*!
* @author Greedysky <greedysky@163.com>
*/
class LoadingProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingProgressWidget(QWidget *parent = nullptr);

    void setDotCount(int count);
    void setDotColor(const QColor &color);

    void setMaxDiameter(float max);
    void setMinDiameter(float min);

    void start();
    void stop();

    virtual QSize sizeHint() const override;

protected:
    void paintDot(QPainter &painter);
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    int m_index;
    int m_count;
    QColor m_dotColor;
    float m_minDiameter, m_maxDiameter;

    int m_interval;
    QTimer m_timer;

    QList<float> m_ranges;
    QList<Position> m_dots;
};

#endif // LOADINGPROGRESSWIDGET_H
