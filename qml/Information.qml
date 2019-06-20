import QtQuick 2.0

Rectangle {
    property alias eScore: score.text
    property alias eBestScore: bestScore.text
    property alias eStep: step.text
    property alias eTotalStep: totalStep.text
    width: 360
    height: 110
    color: "lightyellow"
    Grid{
        columns: 4
        Text{
            width: 90;height: 50
            text: "Score:"
            color: "blue"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id:score
            width: 90;height: 50
            font.bold:true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text{
            width: 90;height: 50
            text: "Best Score:"
            color: "red"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id:bestScore
            width: 90;height: 50
            font.bold:true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text{
            width: 90;height: 50
            text: "Step:"
            color: "blue"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id:step
            width: 90;height: 50
            font.bold:true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text{
            width: 90;height: 50
            text: "Total Step:"
            color: "red"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id:totalStep
            width: 90;height: 50
            font.bold:true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
}
