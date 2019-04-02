#include "mainwindow.h"
#include "dtitlebar.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrlQuery>

static QMap<QString, QString> nameMap = {
    {"申通快递", "shentong"},
    {"顺丰快递", "shunfeng"},
    {"圆通快递", "yuantong"},
    {"中通快递", "zhongtong"},
    {"EMS快递", "ems"},
    {"韵达快递", "yunda"},
    {"天天快递", "tiantian"}
};

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    if (titlebar()) {
        titlebar()->setBackgroundTransparent(true);
        titlebar()->setTitle("快递查询助手");
        titlebar()->setIcon(QIcon(":/sysbro-express.svg"));
    }

    setWindowIcon(QIcon(":/sysbro-express.svg"));
    setWindowTitle("快递查询助手");
    // setWindowRadius(16);

    http = new QNetworkAccessManager;
    mainWidget = new QWidget;
    layout = new QVBoxLayout;
    topLayout = new QHBoxLayout;
    contentLayout = new QHBoxLayout;
    comboBox = new QComboBox;
    numberEdit = new QLineEdit;
    searchButton = new QPushButton("查询");
    contentBox = new QPlainTextEdit;

    contentBox->setWordWrapMode(QTextOption::WrapAnywhere);
    contentBox->setStyleSheet("QPlainTextEdit {"
                              "color: #333333;"
                              "}");

    contentBox->setReadOnly(true);

    topLayout->addWidget(comboBox);
    topLayout->addWidget(numberEdit);
    topLayout->addWidget(searchButton);

    contentLayout->addWidget(contentBox);

    layout->addLayout(topLayout);
    layout->addLayout(contentLayout);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    initComboBoxItem();

    connect(http, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);
    connect(numberEdit, &QLineEdit::returnPressed, this, &MainWindow::query);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::query);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initComboBoxItem()
{
    comboBox->setFocusPolicy(Qt::NoFocus);
    searchButton->setFocusPolicy(Qt::NoFocus);

    for (const QString name : nameMap.keys()) {
        comboBox->addItem(name);
    }
}

void MainWindow::query()
{
    if (numberEdit->text().isEmpty())
        return;

    contentBox->setPlainText("查询中，请稍候...");

    QString type = nameMap[comboBox->currentText()];
    QNetworkRequest request;
    QUrl url("http://api.kuaidi100.com/api");
    QUrlQuery query;
    query.addQueryItem("id", "29833628d495d7a5");
    query.addQueryItem("com", type);
    query.addQueryItem("nu", numberEdit->text());
    query.addQueryItem("show", "0");
    query.addQueryItem("mullti", "1");
    query.addQueryItem("order", "desc");
    url.setQuery(query.toString(QUrl::FullyEncoded));
    request.setUrl(url);

//    request.setUrl(QString("http://api.kuaidi100.com/api?id=29833628d495d7a5&com=%1&nu=%2&show=0&muti=1&order=desc").arg(type).arg(numberEdit->text()));
    http->get(request);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        contentBox->setPlainText("请检查您的网络");
        return;
    }

    QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();

    int value = data.value("status").toString().toInt();

    QString allContent = "";

    if (value != 1) {
        allContent.append("：( 该单号暂无物流进展，请稍后再试，或检查公司和单号是否有误。");
    }else {
        QJsonArray array = data.value("data").toArray();

        for (int i=0; i<array.size(); ++i) {
            allContent.append(array.at(i).toObject().value("time").toString());
            allContent.append("\n");
            allContent.append(array.at(i).toObject().value("context").toString());
            allContent.append("\n\n");
        }
    }

    contentBox->setPlainText(allContent);
}
