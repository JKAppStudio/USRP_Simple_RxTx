import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

RowLayout{
    id: numericControl

    property double value: 0
    property double defaultValue: 0

    property int fontSize: 16
    property alias color: label.color
    property alias name: label.text

    Text{
        id: label
        Layout.alignment: Qt.AlignLeading
        Layout.fillWidth: true
        font.pixelSize: fontSize
    }

    TextField{
        id: textValue
        color: acceptableInput ? label.color : "red"
        text: getTextFromValue(value)
        font.pixelSize: fontSize
        Layout.alignment: Qt.AlignTrailing
        Layout.preferredWidth: 120

        focus: true
        validator: RegExpValidator{ regExp: /^-?\d*\.?\d*[GMkmu]?$/ }

        onAccepted: {
            nextItemInFocusChain(true).focus = true
        }

        onFocusChanged: {
            if(acceptableInput && !focus){
                value = getValueFromText(text)
            }
        }

        Component.onCompleted: {
            value = defaultValue
        }
    }

    function getValueFromText(Str){
        var scale = 1

        switch(Str.charAt(Str.length -1)){
        case "G": scale = 1e9
            break;
        case "M": scale = 1e6
            break;
        case "k": scale = 1e3
            break;
        case "m": scale = 1e-3
            break;
        case "u": scale = 1e-6
            break;
        default: scale = 1
            break;
        }

        return scale*parseFloat(Str)
    }

    function getTextFromValue(number){

        var positiveNumber = Math.abs(number)
        if( positiveNumber/1e9 >= 1 ) return ((number/1e9).toString() + "G")
        if( positiveNumber/1e6 >= 1 ) return ((number/1e6).toString() + "M")
        if( positiveNumber/1e3 >= 1 ) return ((number/1e3).toString() + "k")
        if( positiveNumber < 1 && positiveNumber/1e-3 >= 1 ) return ((number/1e-3).toString() + "m")
        if( positiveNumber < 1 && positiveNumber/1e-6 >= 1 ) return ((number/1e-6).toString() + "u")

        return number.toString();
    }
}
