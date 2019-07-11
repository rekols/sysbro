#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);
    app.loadTranslator();
    app.setOrganizationName("deepin");
    app.setApplicationVersion(DApplication::buildVersion("0.1"));
    app.setApplicationAcknowledgementPage("https://github.com/rekols");
    app.setProductIcon(QIcon(":/images/redict.svg"));
    app.setProductName(DApplication::translate("Main", "Rekols's Dictionary"));
    app.setApplicationDescription(DApplication::translate("Main", "一款 Deepin 平台下的词典，基于 Qt / DTK 开发，占用内存小，使用有道词典 API，内容版权归网易有道公司所有。"));

    MainWindow w;
    w.show();

    QFile file(":/resources/main.qss");
    if (file.open(QIODevice::ReadOnly)) {
        w.setStyleSheet(file.readAll());
        file.close();
    }

    return app.exec();
}
