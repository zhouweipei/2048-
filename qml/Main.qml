import Felgo 3.0
import QtQuick 2.0
import MY2048 1.0
GameWindow {
    id: gameWindow
    activeScene: root
    screenWidth: 360
    screenHeight: 560
    Scene {
        id: root
        property int eI
        function eClear(){
            for(eI=0;eI<16;eI++){
                panel.eNums.itemAt(eI).eNum="";
                panel.eNums.itemAt(eI).color="white";
                panel.eNums.itemAt(eI).eNumColor="black";
            }
        }
        function eShow(){
            eClear();
            if(numProvider.load()===false){
            for(eI=0;eI<16;eI++)
            {
                if(numProvider.show(eI)){
                    panel.eNums.itemAt(eI).eNum=numProvider.show(eI);
                    panel.eNums.itemAt(eI).color=numProvider.color(eI);

                    panel.eNums.itemAt(eI).eNumColor=numProvider.numColor(eI);
                }
           }}

            information.eScore=numProvider.score;
            information.eStep=numProvider.step;
            information.eBestScore=numProvider.bestScore;
            information.eTotalStep=numProvider.totalStep;
            if(numProvider.step>0)
                tip.eEnBack=true;
        }
        Keys.onPressed: {
            switch(event.key){
            case Qt.Key_Up:
                numProvider.move(MY2048.Move_Up);
                root.eShow();
                break;
            case Qt.Key_Down:
                numProvider.move(MY2048.Move_Down);
                root.eShow();
                break;
            case Qt.Key_Left:
                numProvider.move(MY2048.Move_Left);
                root.eShow();
                break;
            case Qt.Key_Right:
                numProvider.move(MY2048.Move_Right);
                root.eShow();
                break;
            default:
                break;
            }

        }
        width: 360
        height: 560

        MY2048{id:numProvider}

        Rectangle{
            id:container
            anchors.fill: parent
            Information{
            id:information

            }
             Panel{
            id:panel
            anchors.centerIn: parent

            }
             Tip{
                 y:460
                id:tip
                onStart: {
                    if(numProvider.load()===false)
                        numProvider.start();

                    root.eShow();
                    root.focus=true;
                    tip.eEnBack=false;
                }
                onBack: {
                    numProvider.backed();
                    root.eShow();
                    if(!numProvider.step)
                        tip.eEnBack=false;
                }
                onExit: {
                     numProvider.save();
                }
             }
        }
    }
}
