import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

RowLayout {

    property alias color: label.color
    property alias model: devicesList.model
    property alias deviceIndex: devicesList.currentIndex

    Text{
        id: label
        text: "Device: "
    }

    ComboBox{
        id: devicesList
        Layout.fillWidth: true
        popup.onOpened: {
            if(popup.visible) model.updateList()
        }
    }

}
