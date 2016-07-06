import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Enterprise.VirtualKeyboard 1.0

Window {
    visible:true
    width: Screen.width
    height: Screen.height

    Item {
        id: root
        anchors.fill: parent

        Text {
            id: text
            text: qsTr("Hello World")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 100
            anchors.top: parent.top
        }
    }
}
