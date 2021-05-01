#ifndef UHDGUIWRAPPER_H
#define UHDGUIWRAPPER_H
#include <QObject>
#include <uhd/usrp/multi_usrp.hpp>
#include "UhdDevicesList.h"

class UHDGUIWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int deviceIndex READ deviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)
    Q_PROPERTY(double rxFrequency READ rxFrequency WRITE setRxFrequency NOTIFY rxFrequencyChanged)
    Q_PROPERTY(double rxGain READ rxGain WRITE setRxGain NOTIFY rxGainChanged)
    Q_PROPERTY(double rxRate READ rxRate WRITE setRxRate NOTIFY rxRateChanged)
public:
    explicit UHDGUIWrapper(QObject *parent = nullptr);
    UhdDevicesList* devicesList() {return &_devices; }

    void setDeviceIndex (int index);
    int deviceIndex() const {return _deviceIndex;}

    //--- RX properties ---------------
    void setRxFrequency(double frequency);
    double rxFrequency();

    void setRxGain(double gain);
    double rxGain();

    void setRxRate(double rate);
    double rxRate();

signals:
    void deviceIndexChanged(int index);
    void rxFrequencyChanged(double frequency);
    void rxGainChanged(double gain);
    void rxRateChanged(double rate);

private:
    UhdDevicesList _devices;
    uhd::usrp::multi_usrp::sptr _usrp;
    int _deviceIndex;
};

#endif // UHDGUIWRAPPER_H
