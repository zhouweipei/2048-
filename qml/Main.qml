import Felgo 3.0
import QtQuick 2.0
import naturEarth 1.0
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
            for(eI=0;eI<16;eI++)
            {
                if(numProvider.show(eI)){
                    panel.eNums.itemAt(eI).eNum=numProvider.show(eI);
                    panel.eNums.itemAt(eI).color=numProvider.color(eI);

                    panel.eNums.itemAt(eI).eNumColor=numProvider.numColor(eI);
                }
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
                    numProvider.start()
                    root.eShow();
                    root.focus=true;
                }

             }
        }
    }
}
