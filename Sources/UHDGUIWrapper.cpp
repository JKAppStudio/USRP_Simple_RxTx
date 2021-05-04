#include "UHDGUIWrapper.h"
#include <iostream>

UHDGUIWrapper::UHDGUIWrapper(QObject *parent): QObject(parent), _devices(UhdDevicesList(parent)), _usrp(nullptr), _deviceIndex(-1)
{
    if(_devices.size() > 0) {
        _usrp = uhd::usrp::multi_usrp::make(_devices.at(0));
        _rx_stream_args = uhd::stream_args_t("fc32");
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

void UHDGUIWrapper::setRxChannel(int channelIndex){

    if(channelIndex == rxChannel() || !_usrp){
        emit rxChannelChanged(-1);
        return;
    }

    std::vector<size_t> channel_nums;
    switch(channelIndex){
    case RF0: channel_nums = { 0 };
        break;
    case RF1: channel_nums = { 1 };
        break;
    case BOTH: channel_nums = { 0, 1 };
        break;
    default: channel_nums = {};
        break;
    }

    _rx_stream_args.channels = channel_nums;

    emit rxChannelChanged(channelIndex);
}

int UHDGUIWrapper::rxChannel(){
    if(!_usrp) return -1;
    if(_rx_stream_args.channels.size() == 0) return -1;
    if(_rx_stream_args.channels.size() > 1) return 2;
    if(_rx_stream_args.channels[0] == 0) return 0;
    return 1;
}

void UHDGUIWrapper::initiateRx(){
    if(!_usrp) return;
    _rx_stream_in_proccess = true;
    emit rxStreamingChanged(_rx_stream_in_proccess);

    if(!_rx_streamer) _rx_streamer = _usrp->get_rx_stream(_rx_stream_args);

    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
    stream_cmd.num_samps = 1024;
    stream_cmd.stream_now = true;
    _rx_buffs.clear();
    _rx_buffs =
            std::vector<std::vector<std::complex<float>>>
            (_usrp->get_rx_num_channels(), std::vector<std::complex<float>>(_rx_streamer->get_max_num_samps()));
    _rx_buff_ptrs.clear();
    for (size_t i = 0; i < _rx_buffs.size(); i++)
        _rx_buff_ptrs.push_back(&_rx_buffs[i].front());

    _rx_streamer->issue_stream_cmd(stream_cmd);
    uhd::rx_metadata_t md;
    _rx_streamer->recv(_rx_buff_ptrs, stream_cmd.num_samps, md, 2);
    if (md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
        throw std::runtime_error("rx streamer error!");
    }

    //    _rx_threads_ptr.push_back(std::thread(UHDGUIWrapper::rxStreaming, this, stream_cmd));
    _rx_stream_in_proccess = false;

    emit rxStreamingChanged(_rx_stream_in_proccess);
    std::cout<< "rx streaming done!\n";
}



bool UHDGUIWrapper::rxStreaming(const UHDGUIWrapper& session, const uhd::stream_cmd_t& cmd){

    //    session._rx_streamer->issue_stream_cmd(cmd);
    //    uhd::rx_metadata_t md;

    //    size_t num_acc_samps = 0; // number of accumulated samples
    //    while (num_acc_samps < cmd.num_samps) {
    //        // receive a single packet
    //        size_t num_rx_samps = session._rx_streamer->recv(session._rx_buff_ptrs, cmd.num_samps, md, 0.1);

    //        // handle the error code
    //        if (md.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT)
    //            return false;
    //        if (md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
    //            throw std::runtime_error(
    //                str(boost::format("Receiver error %s") % md.strerror()));
    //        }

    //        num_acc_samps += num_rx_samps;
    //    }
    std::cout<< "streaming done!\n";
    return true;
}

void UHDGUIWrapper::setRxStreaming(bool stream){

}

bool UHDGUIWrapper::rxStreaming(){
    return _rx_stream_in_proccess;
}
