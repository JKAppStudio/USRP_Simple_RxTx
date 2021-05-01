import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Pane{

    anchors.fill: parent
    focusPolicy: Qt.ClickFocus

    property color textColor: "black"
    property int titleFontSize: 18
    property int textFontSize: 16

    property alias requiredHeight: root.height
    property alias requiredWidth: root.width

    property alias devices: devicesList.model
    property alias deviceIndex: devicesList.deviceIndex

    property alias rxFrequency: rxFrequency.value
    property alias rxGain: rxGain.value
    property alias rxRate: rxRate.value


    GridLayout{
        id: root
        columns: 3

        Text{
            id: title
            color: textColor
            font.pixelSize: titleFontSize
            Layout.columnSpan: root.columns
            Layout.alignment: Qt.AlignCenter
            text: "USRP Settings"

        }

        UHDDevicesList{
            id: devicesList
            Layout.columnSpan: root.columns
        }

        Text{
            color: textColor
            font.pixelSize: textFontSize
            text: qsTr("RX")
            Layout.alignment: Qt.AlignLeading
        }

        MenuSeparator{
            Layout.columnSpan: root.columns - 1
            Layout.alignment: Qt.AlignLeading
        }

        NumericControl{
            id: rxFrequency
            color: textColor
            fontSize: textFontSize
            Layout.columnSpan: root.columns

            name: "Frequency"
            defaultValue: 1e9
        }

        NumericControl{
            id: rxGain
            color: textColor
            fontSize: textFontSize
            Layout.columnSpan: root.columns

            name: "Gain"
            defaultValue: 10
        }

        NumericControl{
            id: rxRate
            color: textColor
            fontSize: textFontSize
            Layout.columnSpan: root.columns

            name: "Rate"
            defaultValue: 1e6
        }
    }
}

