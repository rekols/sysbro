#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>  //Dtk::Widget::moveToCenter(&w); 要调用它，就得引用DWidgetUtil

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator();
    a.setOrganizationName("第七实验室");
    a.setApplicationVersion(DApplication::buildVersion("0.1.0"));
    a.setApplicationAcknowledgementPage("https://github.com/pp710680429/ssf2fcitx");
    a.setProductIcon(QIcon(":/icon/logo"));
    a.setProductName("ssf2fcitx (小盼皮肤转换器)");
    a.setApplicationName("ssf2fcitx"); //只有在这儿修改窗口标题才有效

    MainWindow w;
    w.show();
    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
