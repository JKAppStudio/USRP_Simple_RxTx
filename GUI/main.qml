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
            textColor: "black"
            id: settingsPanel
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

        }
    }

    ChartView{
        anchors.fill: parent
    }
}
