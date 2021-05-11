#include "WaveformDataProvider.h"
#include <iostream>

WaveformDataProvider::WaveformDataProvider(RxDeque *dataDeque, QObject *parent)
    : QObject(parent),
      _dataDeque(dataDeque),
      _pointIndex(0){
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &WaveformDataProvider::update);
    _timer->start(100);
}

void WaveformDataProvider::addSeries(QLineSeries *series){
    if(series) {
        _lineSeries.push_back(series);
    }
}

void WaveformDataProvider::update(){

    if(!_dataDeque || _dataDeque->empty()) return;

    RxBuffer *rx_buff  = _dataDeque->front();
    _dataDeque->pop_front();


    for(size_t i = 0; i < 1; i++){
        ChannelData *channel_data = &rx_buff->at(i);
        QList<QPointF> I;
        QList<QPointF> Q;
        int pointIndex = 0;
        for(auto& point : *channel_data){
            I.append(QPointF(pointIndex, point.real()));
            Q.append(QPointF(pointIndex, point.imag()));
            pointIndex++;
        }
        _lineSeries[i]->replace(I);
        _lineSeries[i+1]->replace(Q);
        _lineSeries[i]->attachedAxes()[0]->setRange(0, 1024);
        _lineSeries[i]->attachedAxes()[1]->setRange(-1e-2, 1e-2);

    }
}
