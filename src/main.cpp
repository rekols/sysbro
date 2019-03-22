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
    a.setApplicationDescription(DApplication::translate("Main", "Sysbro是一款系统助手，可以实时监控CPU、内存占用率、磁盘占用率等等信息，系统清理功能。"));

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
