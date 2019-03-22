#include <DApplication>
#include <DWidgetUtil>
#include "mainwindow.h"

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
    a.setProductIcon(QIcon(":/images/icon.svg"));
    a.setProductName(DApplication::translate("Main", "文件粉碎机"));
//    a.setApplicationDescription(DApplication::translate("Main", "网络测速"));

    if (!a.setSingleInstance("sysbro-network-test")) {
        return 0;
    }

    MainWindow w;
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();

}
