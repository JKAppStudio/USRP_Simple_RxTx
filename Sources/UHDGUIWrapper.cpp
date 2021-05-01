#include "UHDGUIWrapper.h"
#include <iostream>

UHDGUIWrapper::UHDGUIWrapper(QObject *parent): QObject(parent), _devices(UhdDevicesList(parent)), _usrp(nullptr), _deviceIndex(-1)
{
    if(_devices.size() > 0) {
        _usrp = uhd::usrp::multi_usrp::make(_devices.at(0));
        _deviceIndex = 0;
    }
}

void UHDGUIWrapper::setDeviceIndex(int index){
    if (index == _deviceIndex) return;
    if(index < 0) {
        _usrp.reset();
        _deviceIndex = index;
        return;
    }
    if(_deviceIndex >= 0) _usrp.reset();
    if(size_t(index) < _devices.size()){
        _usrp = uhd::usrp::multi_usrp::make(_devices.at(size_t(index)));
        _deviceIndex = index;
    }
}

void UHDGUIWrapper::setRxFrequency(double frequency){
    if(!_usrp) return;
    if(frequency == rxFrequency()) return;

    _usrp->set_rx_freq(frequency);
    emit rxFrequencyChanged(rxFrequency());
}

double UHDGUIWrapper::rxFrequency(){
    if(!_usrp) return 0;
    return _usrp->get_rx_freq();
}

void UHDGUIWrapper::setRxGain(double gain){
    if(!_usrp) return;
    if(gain == rxGain()) return;

    _usrp->set_rx_gain(gain);
    emit rxGainChanged(rxGain());
}

double UHDGUIWrapper::rxGain(){
    if(!_usrp) return 0;
    return _usrp->get_rx_gain();
}

void UHDGUIWrapper::setRxRate(double rate){
    if(!_usrp) return;
    if (rate == rxRate()) return;

    _usrp->set_rx_rate(rate);
    emit rxRateChanged(rxRate());

}

double UHDGUIWrapper::rxRate(){
    if(!_usrp) return 0;
    return _usrp->get_rx_rate();
}
