import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    property alias eEnBack: back.enabled
    signal start()
    signal back()
    signal exit()
    signal load()
    width: 360
    height: 180
    Button{
        width: 90;height: 100
        text:qsTr("新游戏")
        onClicked: parent.start();
    }
    Button{
        id:back
        width: 90;height: 100
        x:90
        text:qsTr("撤销")
        enabled: false
        onClicked: parent.back();
    }
    Button{

        width: 90;height: 100
        x:180
        text:qsTr("存档")
        onClicked: parent.exit();
    }
    Button{
        x:270
        width: 90;height: 100
        text:qsTr("读档")
        onClicked: parent.load();
    }



}
