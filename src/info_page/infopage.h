#ifndef INFOPAGE_H
#define INFOPAGE_H

#include <QWidget>
#include <QVBoxLayout>

class InfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit InfoPage(QWidget *parent = 0);

private:
    void initInfo();

private:
    QVBoxLayout *m_contentLayout;
};

#endif // INFOPAGE_H
