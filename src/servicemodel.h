#ifndef SPEEDUPMODEL_H
#define SPEEDUPMODEL_H

#include <QAbstractTableModel>

class ServiceItem
{
public:
    QString name;
    QString description;
    bool status;

    inline bool operator==(const ServiceItem &other) {
        return other.name == name &&
                other.description == description &&
                other.status == status;
    }
};

class ServiceModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum DataRole {
        Name,
        Description,
        Status
    };

    explicit ServiceModel(QObject *parent = nullptr);

    void loadServices();
    QString getDescription(const QString &name);
    void switchStatus(QModelIndex idx);
    void checkEnableItem();

signals:
    void requestServicesNumber(int number);

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<ServiceItem *> m_serviceList;
};

#endif // SPEEDUPMODEL_H
