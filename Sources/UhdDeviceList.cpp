#include "UhdDevicesList.h"
#include <iostream>

UhdDevicesList::UhdDevicesList(QObject *parent): QAbstractListModel(parent){
    updateList();
}

QHash <int,QByteArray> UhdDevicesList::roleNames() const {
    static QHash <int, QByteArray> mapping {
        {DEVICE, "device"}
    };
    return mapping;
}

int UhdDevicesList::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) return 0;

    return _devices.size();
}

QVariant UhdDevicesList::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QVariant();

    const uhd::device_addr_t &device = _devices.at(index.row());
    if(role == DEVICE) return QString(device.get("product").c_str()) + " " + QString(device.get("serial").c_str());

    return QVariant();
}

void UhdDevicesList::updateList(){

    beginResetModel();
    uhd::device_addr_t device_filter(""); //find ANY device connected to system
    _devices = uhd::device::find(device_filter);
    endResetModel();
}
