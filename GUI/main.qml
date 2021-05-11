import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtCharts 2.3
import "../GUI/Controls"

ApplicationWindow {
    id: window
    width: 800
    height: 480
    visible: true
    title: qsTr("USRP Simple Rx Tx")
    minimumWidth: settingsPanel.requiredWidth + 50
    minimumHeight: settingsPanel.requiredHeight + 50


    Drawer{
        id: settings
        height: window.height
        dragMargin: window.width * 0.08
        Component.onCompleted: open()

        USRPControlPanel{
            id: settingsPanel
            textColor: window.color > "#555555" ? "black" : "lightgray"
            devices: __usrpList

            onDeviceIndexChanged: __USRPSession.deviceIndex = deviceIndex

            onRxFrequencyChanged: {
                if(__USRPSession.rxFrequency !== rxFrequency){
                    __USRPSession.rxFrequency = rxFrequency
                    rxFrequency = __USRPSession.rxFrequency
                }
            }

            onRxGainChanged: {
                if(__USRPSession.rxGain !== rxGain){
                    __USRPSession.rxGain = rxGain
                    rxGain = __USRPSession.rxGain
                }
            }

            onRxRateChanged: {
                if(__USRPSession.rxRate !== rxRate){
                    __USRPSession.rxRate = rxRate
                    rxRate = __USRPSession.rxRate
                }
            }

            onRxChannelChanged: {
                if(__USRPSession.rxChannel !== rxChannel)
                    __USRPSession.rxChannel = rxChannel
                rxChannel = __USRPSession.rxChannel
            }
        }
    }

    Pane{
        anchors.fill: parent

        GridLayout{

            anchors.fill: parent
            columns:2

            ToggleButton{
                id: startRx
                onText: "Stop RX"
                offText: "Start RX"

                isActive:
                    (__USRPSession != null) ? __USRPSession.rxStreaming : false // protection in case __USRPSession destroyed

                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 0

                onPressed: {
                    if(!isActive) __USRPSession.initiateRx()
                }
            }

            ToggleButton{
                id: startTx
                onText: "Stop TX"
                offText: "Start TX"

                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 1
            }

            ChartView{
                id: rxSignalChart
                Layout.rowSpan: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 0
                Layout.row: 0

//                theme: ChartView.ChartThemeBrownSand

                animationOptions: ChartView.NoAnimation
                antialiasing: true
                legend.alignment: Qt.AlignRight

                LineSeries{
                    id: rxSignal0_I
                    name: "rx0 I"
                    useOpenGL: true

                }

                LineSeries{
                    id: rxSignal0_Q
                    name: "rx0 Q"
                    useOpenGL: true

                }

                Component.onCompleted: {
                    for(var i=0; i < rxSignalChart.count; i++)
                   __rxSignalProvider.addSeries(rxSignalChart.series(i))
                }

            }


        }
    }
}
