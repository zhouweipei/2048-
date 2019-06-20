import QtQuick 2.0
import QtQuick.Dialogs 1.1
MessageDialog{
    property alias M_id: id
    id:messageDialog
    title: Save&Exit
    informativeText:"Do you want Save&Exit?"
    standardButtons: StandardButton.Yes|StandardButton.Cancel
    onYes: {yesClicked()}
    onNo: {onClicked()}
}
