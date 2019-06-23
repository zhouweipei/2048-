
import Felgo 3.0
import QtQuick 2.0
import MY2048 1.0
GameWindow {
    id: gameWindow
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
        }//清理方块
        function eShow(){
            eClear();


                 for(eI=0;eI<16;eI++)
                 {
                    if(numProvider.show(eI)!==0){
                        panel.eNums.itemAt(eI).eNum=numProvider.show(eI);//数字
                        panel.eNums.itemAt(eI).color=numProvider.color(eI);//方块颜色
                        panel.eNums.itemAt(eI).eNumColor=numProvider.numColor(eI);//数字颜色
                    }
                  }


            information.eScore=numProvider.score;
            information.eStep=numProvider.step;
            information.eBestScore=numProvider.bestScore;
            information.eTotalStep=numProvider.totalStep;
            if(numProvider.step>0)
                tip.eEnBack=true;
{
//            if(numProvider.load()===true){

//                 for(eI=0;eI<16;eI++)
//                 {
//                    if(numProvider.show(eI)!==0){
//                        panel.eNums.itemAt(eI).eNum=numProvider.show(eI);
//                        panel.eNums.itemAt(eI).color=numProvider.color(eI);
//                        panel.eNums.itemAt(eI).eNumColor=numProvider.numColor(eI);
//                    }
//                  }


//            information.eScore=numProvider.score;
//            information.eStep=numProvider.step;
//            information.eBestScore=numProvider.bestScore;
//            information.eTotalStep=numProvider.totalStep;
//            if(numProvider.step>0)
//                tip.eEnBack=true;
//        }
}
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

        }//键盘响应

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
                    numProvider.start();
                    root.eShow();
                    root.focus=true;
                    tip.eEnBack=false;
                }
                property int  i:3
                onBack: {
                    i--
                    numProvider.backed();
                    root.eShow();
                    if(!numProvider.step||i===0)
                        tip.eEnBack=false;
                }
                onSave: {
                     numProvider.save();
                }
                onLoad: {
                    numProvider.load();
                    root.eShow();
                }
             }
        }
    }
//   DirButton{

//    id:dirButton
//    onRight: {
//        numProvider.move(MY2048.Move_Right)
//            root.eShow()
//    }
//    onLeft: {
//        numProvider.move(MY2048.Move_Left)
//            root.eShow()
//    }
//    onDown: {
//        numProvider.move(MY2048.Move_Down)
//            root.eShow()

//    }
//    onUp: {
//        numProvider.move(MY2048.Move_Up)
//        root.eShow()
//    }
//   }
//    ExitButton{
//        x:gameWindow.width*4/5
//        y:gameWindow.height/2
//        onExit: {
//            numProvider.exit()
//        }

//    }


}
