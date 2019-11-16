#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QSettings>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private:
    void handleCurrentIndexChanged(int index);

signals:
    void startButtonClicked(int index);

private:
    QComboBox *m_comboBox;
    QSettings *m_settings;
};

#endif // HOMEPAGE_H
