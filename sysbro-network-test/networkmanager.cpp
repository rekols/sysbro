#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkProxy>

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
}

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_fakeReply(nullptr),
      m_realReply(nullptr)
{
    m_networkManager->setProxy(QNetworkProxy::NoProxy);
}

void NetworkManager::startTest()
{
    QNetworkRequest request(QUrl("http://dlied6.qq.com/invc/xfspeed/qqpcmgr/download/Test216MB.dat"));
    m_fakeReply = m_networkManager->get(request);
    connect(m_fakeReply, &QNetworkReply::finished, this, &NetworkManager::handleFakeReplyFinished);
}

void NetworkManager::handleFakeReplyFinished()
{
//    if (m_fakeReply == nullptr) {
//        return;
//    }

    int statusCode = m_fakeReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 302) {
        QString redirectUrl = m_fakeReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
        qDebug() << "redirected to: " << redirectUrl;

        QNetworkRequest request(redirectUrl);
        m_realReply = m_networkManager->get(request);

        QTime downloadTime;
        downloadTime.start();

        m_speedList.clear();

        connect(m_realReply, &QNetworkReply::downloadProgress, this, [=] (qint64 bytesReceived, qint64 bytesTotal) {
            quint64 speed = bytesReceived * 1000.0 / downloadTime.elapsed();
            m_speedList << speed;

            qDebug() << m_speedList.indexOf(speed) << formatBytes(speed);

            emit statusChanged(formatBytes(speed));

            if (m_speedList.size() >= 60) {
                m_realReply->abort();

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
        });
    } else {
        emit testFailed();
    }
}
