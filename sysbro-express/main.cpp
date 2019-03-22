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
    a.setProductIcon(QIcon(":/sysbro-express.svg"));
    a.setProductName(DApplication::translate("Main", "快递查询助手"));
    a.setApplicationDescription(DApplication::translate("Main", "一款快递查询助手，查询信息由快递110提供服务"));

    if (!a.setSingleInstance("sysbro-express")) {
        return 0;
    }

    MainWindow w;
    w.setFixedSize(500, 380);
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();

}
