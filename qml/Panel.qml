//画方块
import QtQuick 2.0

Rectangle {
    property var eNums: repeater
    id:root
    width: 360-radius*2
    height: width
    color: "lightblue"
    radius: 20
    Grid{
        id:grid
        columns: 4
        anchors.centerIn: parent
        spacing: 10
        Repeater{
            id:repeater
            model: 16
            MyItem{
                width: (root.width-grid.spacing*5)/4
                height: width
            }
        }
    }
}
