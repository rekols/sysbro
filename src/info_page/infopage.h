#ifndef INFOPAGE_H
#define INFOPAGE_H

#include <QWidget>
#include <QVBoxLayout>

class InfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit InfoPage(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initInfo();

private:
    QVBoxLayout *m_contentLayout;
};

#endif // INFOPAGE_H
