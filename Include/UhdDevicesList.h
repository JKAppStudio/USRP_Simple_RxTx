#ifndef UHDDEVICESLIST_H
#define UHDDEVICESLIST_H
#include <QAbstractListModel>
#include <uhd/device.hpp>

class UhdDevicesList: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit UhdDevicesList(QObject *parent = nullptr);
    enum Roles{
        DEVICE = Qt::UserRole
    };

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash <int, QByteArray> roleNames() const override;
    size_t size() const {return _devices.size(); }
    uhd::device_addr_t at(size_t index) const {return _devices.at(index);}

public slots:
    void updateList();
private:
    uhd::device_addrs_t _devices;
};

#endif // UHDDEVICESLIST_H
