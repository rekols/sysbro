#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QRegularExpression>
#include <QDebug>

static QString formatBytes(quint64 bytes)
{
    if (bytes < 1024)
        return QString::number(bytes, 'r', 1) + "B/s";

    else if (bytes / 1024 < 1024)
        return QString::number(bytes / 1024.0, 'r', 1) + "KB/s";

    else if (bytes / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024.0 / 1024.0, 'r', 1) + "MB/s";

    else if (bytes / 1024 / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024.0 / 1024.0 / 1024.0, 'r', 1) + "GB/s";

    return QString();
}

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_realReply(nullptr)
{
    m_networkManager->setProxy(QNetworkProxy::NoProxy);
}

void NetworkManager::startTest(int server_index)
{
    switch (server_index) {
    case 0:
        // 百度服务器
        m_realUrl = "http://bos.nj.bpc.baidu.com/v1/baiduplayer/player/BaiduPlayer5Setup_5.exe";
        break;
    case 1:
        // 阿里服务器
        m_realUrl = "https://download.alicdn.com/wangwang/AliIM2019_taobao(9.12.07C).exe";
        break;
    case 2:
        // 腾讯服务器
        m_realUrl = "https://dldir1.qq.com/qqfile/qq/PCQQ9.1.5/25530/QQ9.1.5.25530.exe";
        break;
    default:
        m_realUrl = "";
        break;
    }

    realTest();
}

void NetworkManager::realTest()
{
    qDebug() << "start: " << m_realUrl;

    QNetworkRequest request(m_realUrl);
    m_realReply = m_networkManager->get(request);

    m_downloadTime.start();
    m_speedList.clear();

    connect(m_realReply, &QNetworkReply::finished, this, &NetworkManager::testFailed);
    connect(m_realReply, &QNetworkReply::downloadProgress, this, &NetworkManager::handleDownloadProgress);
}

void NetworkManager::handleDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    quint64 speed = bytesReceived * 1000.0 / m_downloadTime.elapsed();
    m_speedList << speed;

    qDebug() << m_speedList.indexOf(speed) << formatBytes(speed);

    emit requestPercent(m_speedList.indexOf(speed) / 60.0 * 100);
    emit statusChanged(formatBytes(speed));

    if (m_speedList.size() >= 60 || bytesReceived == bytesTotal) {
        m_realReply->abort();
        m_realReply->deleteLater();

        // quint64 total = 0;
        // for (quint64 bytes : m_speedList) {
        //     total += bytes;
        // }

        // total = total / m_speedList.size();

        quint64 speedBytes = 0;
        for (quint64 bytes : m_speedList) {
            if (bytes > speedBytes) {
                speedBytes = bytes;
            }
        }

        qDebug() << "success: " << formatBytes(speedBytes);

        emit testSuccess(speedBytes, formatBytes(speedBytes));
    }
}
