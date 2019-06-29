#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonImport_clicked();

    void on_pushButtonTransformation_clicked();

    void on_pushButtonViewLocationSkin_clicked();

    void on_pushButtonDeleteLocationSkin_clicked();

private:
    Ui::Widget *ui;

    QString 转换程序;
    QProcess * process;
    QStringList ssf文件;
    QString 安装存放目录_字符串; //$HOME/.config/fcitx/skin

    bool DeleteDirectory(const QString &path);
};

#endif // WIDGET_H
