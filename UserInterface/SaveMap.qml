import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.2

FocusScope {
    width: childrenRect.width
    height: childrenRect.height

    Row {
        Button {
            text: "SaveMap"
            onClicked: saveMap.toggleEnabled()
        }

        Row {
            enabled: visible
            visible: saveMap.enabled

            Column {
                Row {
                    Button {
                        text: "Save to file:"
                        onClicked: {
                            if (fileName.mapPath !== "")
                                saveMap.dump(fileName.mapPath);
                        }
                    }

                    Button {
                        property string mapPath

                        id: fileName
                        text: mapPath === "" ? "Open..." : mapPath
                        onClicked: fileDialog.visible = true
                    }

                    FileDialog {
                        id: fileDialog
                        selectExisting: false
                        onAccepted: fileName.mapPath = fileDialog.fileUrls[0]
                        onVisibleChanged: app.allowLockCursor = !visible
                    }
                }
            }
        }
    }
}
