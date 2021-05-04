import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    property alias textSize: label.font.pixelSize
    property alias label: label.text
    property alias color: label.color
    property alias index: selector.currentIndex

    Text {
        id: label
        Layout.fillWidth: true
    }

    ComboBox{
        id: selector
        model: ["RF0", "RF1", "both"]
    }

}
