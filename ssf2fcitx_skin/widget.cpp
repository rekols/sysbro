#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QFileInfoList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    转换程序 = QCoreApplication::applicationDirPath() + "/ssf2skin";

    //new变量和建立一些局部变量
    安装存放目录_字符串 = QString(QDir::homePath() + "/.config/fcitx/skin/");
    QDir 安装存放目录(安装存放目录_字符串);
    process =new QProcess;

    //先检查目录存在不，若是不存在，则先建立
    if(!安装存放目录.exists()){
        if(!安装存放目录.mkdir(安装存放目录_字符串)) ;
        QMessageBox::warning(0,tr("提示"),QString("安装存放目录“%1”不存在，请检查！").arg(安装存放目录_字符串),QMessageBox::Ok);
    }


    //检查 转换程序 是否存在
    QtConcurrent::run([=](){
        QFileInfo fileInfo(转换程序);
        if(!fileInfo.isFile())
        {
            QMessageBox::warning(0,tr("提示"),QString("缺少组件%1,请重新安装软件！").arg(转换程序),QMessageBox::Ok);
        }
    });

    //设置背景图片
    //    this->setAutoFillBackground(true);
    //    QPalette palette = this->palette();
    //    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/icon/background").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    //    this->setPalette(palette);// 给widget加上背景图


    //QListWidget设置多选
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonImport_clicked()
{
    ui->pushButtonDeleteLocationSkin->setEnabled(false);
    ui->pushButtonTransformation->setEnabled(true);

    ssf文件 = QFileDialog::getOpenFileNames(
                this,
                tr("请选择ssf文件（搜狗皮肤）"),
                QDir::homePath(),
                "ssf (*.ssf)");

    //如果没有选择，就直接返回
    if(ssf文件.isEmpty()) return;

    //清空旧的列表项
    ui->listWidget->clear();

    //如果选择了文件，则把文件显示在列表中
    for(QString 单个文件 : ssf文件){
        ui->listWidget->addItem(单个文件);
    }
}

void Widget::on_pushButtonTransformation_clicked()
{
    //如果列表是空，则直接返回
    if(ui->listWidget->count() == 0){
        return ;
    }

    //开始进行转换
    for(QString 单个文件: ssf文件){
        int first = 单个文件.lastIndexOf ("/");
        QString 保存文件名 = 单个文件.right (单个文件.length ()-first-1);
        保存文件名 = 保存文件名.replace(".ssf","");
        保存文件名 = 安装存放目录_字符串 + 保存文件名;
        //qDebug() << 保存文件名;
        process->start(转换程序 , QStringList() << "-i" << 单个文件 << "-o" << 保存文件名);
        process->waitForFinished();
    }

    QMessageBox::information(0,tr("提示"),QString("转换完毕！请检查！"),QMessageBox::Ok);
}


void Widget::on_pushButtonViewLocationSkin_clicked()
{
    ui->pushButtonDeleteLocationSkin->setEnabled(true);
    ui->pushButtonTransformation->setEnabled(false);

    ui->listWidget->clear();
    int fileCount = 0;
    QDir 本地皮肤存放目录(安装存放目录_字符串);
    QFileInfoList fileInfoList = 本地皮肤存放目录.entryInfoList();
    foreach ( QFileInfo fileInfo, fileInfoList )
    {
        if ( fileInfo.fileName() == "." || fileInfo.fileName() == ".." )
            continue;
        fileCount++;

        if ( fileInfo.isDir() )
        {
            //qDebug() << fileInfo.fileName();

            //如果是目录就加入到列表中显示
            ui->listWidget->addItem(fileInfo.fileName());
        }
    }
}

void Widget::on_pushButtonDeleteLocationSkin_clicked()
{
    //如果没有选中，就直接返回
    if(ui->listWidget->selectedItems().count() == 0){
        return;
    }

    //弹出提示框，再次确认后才删除
    int 选中状态 = QMessageBox::warning(this,tr("提示"),tr("在你删除前，你一定要再次确认选中的是你要删除的！"),QMessageBox::Ok,QMessageBox::Cancel);
    if(选中状态 == QMessageBox::Cancel){
        return;
    }

    //删除
    QDir tmpDir(安装存放目录_字符串);
    for(int i = 0;i < ui->listWidget->selectedItems().count() ;i++){
        QString 要删除的目录 = 安装存放目录_字符串 + QString(ui->listWidget->selectedItems()[i]->text());
        if(!DeleteDirectory(要删除的目录)){
            选中状态 = QMessageBox::warning(this,tr("提示"),QString("删除“%1”失败！点击OK继续，否则将停止删除！").arg(要删除的目录),QMessageBox::Ok,QMessageBox::Cancel);
            if(选中状态 == QMessageBox::Cancel){
                break;
            }
        }
    }

    //删除完刷新显示列表
    on_pushButtonViewLocationSkin_clicked();
}

//这个函数来自--->https://www.jianshu.com/p/7a65d539cfef<---的代码
bool Widget::DeleteDirectory(const QString &path)
{
    if (path.isEmpty())
    {
        return false;
    }

    QDir dir(path);
    if(!dir.exists())
    {
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            fi.dir().remove(fi.fileName());
        }
        else
        {
            DeleteDirectory(fi.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}
