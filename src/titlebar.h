#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);

signals:
    void tabbarCurrentChanged(int index);

private:
    QHBoxLayout *m_layout;
};

#endif // TITLEBAR_H
