#ifndef UHDGUIWRAPPER_H
#define UHDGUIWRAPPER_H
#include <QObject>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/thread.hpp>
#include <vector>
#include <deque>
#include <chrono>
#include <complex>
#include <thread>
#include "UhdDevicesList.h"

enum ChannelSelector{
    RF0,
    RF1,
    BOTH
};

using Complex = std::complex<float>;
using ChannelData = std::vector<Complex>;
using RxBuffer = std::vector<ChannelData>;
using RxBuf_ptrs = std::vector<Complex*>;
using RxDeque = std::deque<RxBuffer*>;

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

    RxDeque* rxDeque();

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
    static std::vector<std::thread> _rx_threads_ptrs;

    UhdDevicesList _devices;
    int _deviceIndex;

    uhd::usrp::multi_usrp::sptr _usrp;

    uhd::stream_args_t _rx_stream_args;
    uhd::rx_streamer::sptr _rx_streamer;
    RxBuffer _rx_buffs;
    RxBuf_ptrs _rx_buff_ptrs;
    RxDeque _rx_deque;

    bool _rx_stream_in_proccess;
};


#endif // UHDGUIWRAPPER_H
