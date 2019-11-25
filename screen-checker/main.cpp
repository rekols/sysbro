#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    const QString appName = "sysbro-screen-checker";
    const QString tsPath = QString("/usr/share/%1/translations/%2_%3.ts").arg(appName).arg(appName).arg(QLocale::system().name());

    if (qtTranslator.load(tsPath)) {
        a.installTranslator(&qtTranslator);
    }

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
