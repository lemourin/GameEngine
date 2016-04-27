import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2

FocusScope {
    width: childrenRect.width
    height: childrenRect.height

    Row {
        Button {
            text: "LoadMap"
            onClicked: loadMap.toggleEnabled()
        }

        Row {
            enabled: visible
            visible: loadMap.enabled

            Column {
                Row {
                    Button {
                        text: "Load from file:"
                        onClicked: {
                            if (fileName.mapPath !== "")
                                loadMap.load(fileName.text);
                        }
                    }

                    Button {
                        property string mapPath: ""

                        id: fileName
                        text: mapPath == "" ? "Open..." : mapPath
                        onClicked: fileDialog.visible = true
                    }

                    FileDialog {
                        id: fileDialog
                        onAccepted: fileName.mapPath = fileDialog.fileUrls[0]
                        onVisibleChanged: app.allowLockCursor = !visible
                    }
                }
            }
        }
    }
}
