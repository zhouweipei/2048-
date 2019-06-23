//方向键
import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    signal right()
    signal left()
    signal down()
    signal up()
    width: 180;height: 180
    Button{
        x:60
        width: 60;height: 60
        text: qsTr("向上")
        onClicked: parent.up()
    }
    Button{
        y:60
        width: 60;height: 60
        text: qsTr("向左")
        onClicked: parent.left()
    }
    Button{
        x:120
        y:60
        width: 60;height: 60
        text: qsTr("向右")
        onClicked: parent.right()
    }
    Button{
        x:60
        y:120
        width: 60;height: 60
        text: qsTr("向下")
        onClicked: parent.down()
    }
}
