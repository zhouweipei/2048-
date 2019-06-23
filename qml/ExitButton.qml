//退出按钮
import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    signal exit()
    Button{
        width: 60;height: 60
        text: qsTr("Exit")
        onClicked: parent.exit()
    }


}
