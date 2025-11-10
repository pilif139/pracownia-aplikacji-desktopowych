import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "File Manager App"

    menuBar: MenuBar {
        Menu {
            title: "&File"

            MenuItem {
                text: "&Save File"
                onTriggered: saveFileDialog.open()
            }

            MenuItem {
                text: "&Load File"
                onTriggered: loadFileDialog.open()
            }

            MenuSeparator {}

            MenuItem {
                text: "&Quit"
                onTriggered: Qt.quit()
            }
        }
    }

    FileDialog {
        id: saveFileDialog
        title: "Save File"
        nameFilters: ["Text files (*.txt)", "All files (*)"]
        onAccepted: {
            FileHandler.saveFile(fileUrl)
        }
    }

    FileDialog {
        id: loadFileDialog
        title: "Load File"
        nameFilters: ["Text files (*.txt)", "All files (*)"]
        onAccepted: {
            FileHandler.loadFile(fileUrl)
        }
    }
}
