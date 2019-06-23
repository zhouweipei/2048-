//底部按钮
import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    property alias eEnBack: back.enabled
    signal start()
    signal back()
    signal save()
    signal load()
    width: 360
    height: 180
    Button{
        width: 90;height: 100
        text:qsTr("New Game")
        onClicked: parent.start();
    }
    Button{
        id:back
        width: 90;height: 100
        x:90
        text:qsTr("Back")
        enabled: false
        onClicked: parent.back();
    }
    Button{

        width: 90;height: 100
        x:180
        text:qsTr("Save")
        onClicked: parent.save();
    }
    Button{
        x:270
        width: 90;height: 100
        text:qsTr("Load")
        onClicked: parent.load();
    }



}
