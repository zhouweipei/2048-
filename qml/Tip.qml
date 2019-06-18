import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    signal start()
    signal back()
    signal exit()
    width: 360
    height: 180
    Button{
        width: 120;height: 100
        text:qsTr("Start")
        onClicked: parent.start();
    }
    Button{
        width: 120;height: 100
        x:120
        text:qsTr("Back")
        onClicked: parent.back();
    }
    Button{
        width: 120;height: 100
        x:240
        text:qsTr("Exit")
        onClicked: parent.exit();
    }


}
