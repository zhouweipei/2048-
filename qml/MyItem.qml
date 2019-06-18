import QtQuick 2.0

Rectangle {
    property alias eNum: innerNum.text
    property alias eNumColor: innerNum.color
    width: 50;height: 50
    color: "white"
    radius: 10
    Text {
        id: innerNum
        anchors.centerIn: parent
        color: "black"
        font.bold: true
    }
}
