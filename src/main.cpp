#include <DApplication>
#include <DWidgetUtil>
#include "mainwindow.h"
#include "utils.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator();
    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("1.0"));
    a.setApplicationAcknowledgementPage("https://github.com/rekols");
    a.setProductIcon(QIcon(":/resources/sysbro.svg"));
    a.setProductName(DApplication::translate("Main", "SysBro"));
    a.setApplicationDescription(DApplication::translate("Main", "Sysbro is a system assistant that monitors CPU, memory and more..."));

    if (!a.setSingleInstance("assistant")) {
        return 0;
    }

    MainWindow w;
    w.show();
    w.setWindowIcon(QIcon(":/resources/sysbro.svg"));
    w.setStyleSheet(Utils::getFileContent(":/resources/style.qss"));

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
