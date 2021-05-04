#ifndef UHDGUIWRAPPER_H
#define UHDGUIWRAPPER_H
#include <QObject>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/thread.hpp>
#include <vector>
#include <chrono>
#include <complex>
#include <thread>
#include "UhdDevicesList.h"

enum ChannelSelector{
    RF0,
    RF1,
    BOTH
};

class UHDGUIWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int deviceIndex READ deviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)
    Q_PROPERTY(double rxFrequency READ rxFrequency WRITE setRxFrequency NOTIFY rxFrequencyChanged)
    Q_PROPERTY(double rxGain READ rxGain WRITE setRxGain NOTIFY rxGainChanged)
    Q_PROPERTY(double rxRate READ rxRate WRITE setRxRate NOTIFY rxRateChanged)
    Q_PROPERTY(int rxChannel READ rxChannel WRITE setRxChannel NOTIFY rxChannelChanged)
    Q_PROPERTY(bool rxStreaming READ rxStreaming WRITE setRxStreaming NOTIFY rxStreamingChanged)

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

    void setRxChannel(int channelIndex);
    int rxChannel();

    void setRxStreaming(bool stream);
    bool rxStreaming();

signals:
    void deviceIndexChanged(int index);
    void rxFrequencyChanged(double frequency);
    void rxGainChanged(double gain);
    void rxRateChanged(double rate);
    void rxChannelChanged(int channelIndex);
    void rxStreamingChanged(bool inProcess);

public slots:
    void initiateRx();

private:
    UhdDevicesList _devices;
    uhd::usrp::multi_usrp::sptr _usrp;
    int _deviceIndex;
    uhd::stream_args_t _rx_stream_args;
    uhd::rx_streamer::sptr _rx_streamer;
    std::vector<std::vector<std::complex<float>>> _rx_buffs;
    std::vector<std::complex<float>*> _rx_buff_ptrs;
    std::vector<std::thread> _rx_threads_ptr;
    bool _rx_stream_in_proccess;

    static bool rxStreaming(const UHDGUIWrapper& session, const uhd::stream_cmd_t& cmd);

};

#endif // UHDGUIWRAPPER_H
