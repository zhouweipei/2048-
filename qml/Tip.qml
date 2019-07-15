//底部按钮
import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    property alias eEnBack: back.enabled
    property alias eEnReordering: reordering.enabled
    signal start()
    signal back()
    signal save()
    signal load()
    signal reordering()
    width: 360
    height: 180
    Button{
        width: 72;height: 100
        text:qsTr("New Game")
        onClicked: parent.start();
    }
    Button{
        id:back
        width: 72;height: 100
        x:72
        text:qsTr("Back")
        enabled: false
        onClicked: parent.back();
    }
    Button{

        width: 72;height: 100
        x:144
        text:qsTr("Save")
        onClicked: parent.save();
    }
    Button{
        x:216
        width: 72;height: 100
        text:qsTr("Load")
        onClicked: parent.load();
    }
    Button{
        x:288
        id:reordering
        width: 72; height:100
        text: qsTr("Reordering")
        onClicked: parent.reordering()
        enabled: true
    }



}
