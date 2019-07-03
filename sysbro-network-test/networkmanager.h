#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);

    void startTest(int server_index);
    void realTest();

signals:
    void statusChanged(QString speed);
    void testSuccess(quint64 speed, QString speedStr);
    void requestPercent(int value);
    void testFailed();

private:
    void handleDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_realReply;
    QList<qint64> m_speedList;
    QTime m_downloadTime;
    QString m_realUrl;
};

#endif // NETWORKMANAGER_H
