import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    property string onText: "On"
    property string offText: "Off"
    property bool isActive: false

    text: isActive ? onText : offText
//    onPressed: isActive = !isActive
}
