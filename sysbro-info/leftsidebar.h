#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

class LeftSideBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftSideBar(QWidget *parent = 0);

signals:
    void buttonClicked(int index);

private:
    void paintEvent(QPaintEvent *);
    void initButtons();

private:
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonGroup;
    QStringList m_buttonNameList;
};

#endif // LEFTSIDEBAR_H
