#ifndef WAVEFORMDATAPROVIDER_H
#define WAVEFORMDATAPROVIDER_H

#include <QObject>
#include <QtCharts>
#include <QTimer>
#include <vector>
#include <complex>
#include <deque>

using Complex = std::complex<float>;
using ChannelData = std::vector<Complex>;
using RxBuffer = std::vector<ChannelData>;
using RxBuf_ptrs = std::vector<Complex*>;
using RxDeque = std::deque<RxBuffer*>;

class WaveformDataProvider: public QObject{
    Q_OBJECT

public:
    Q_INVOKABLE void addSeries(QLineSeries *series);
    explicit WaveformDataProvider(RxDeque *dataDeque, QObject *parent = nullptr);


private:
    RxDeque *_dataDeque;
    QVector<QLineSeries*> _lineSeries;

    QTimer *_timer;
    int _pointIndex;

    void update();
};

#endif // WAVEFORMDATAPROVIDER_H
