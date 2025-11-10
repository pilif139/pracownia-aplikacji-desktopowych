import QtQuick
import QtQuick.Controls
import zadanie_domowe 1.0

Drawer{
    id: addTaskDrawer
    width: parent.width
    height: parent.height/2
    edge: Qt.BottomEdge
    background: Rectangle{
        anchors.fill: parent
        color: "#f0f0f0"
        Label{
            id: titleLabel
            text: "Add New"
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            anchors.top: parent.top
            anchors.topMargin: 10
            color: "black"
        }
        TextField{
            id: titleInput
            placeholderText: "Task Title"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: titleLabel.bottom
            anchors.topMargin: 20
            width: parent.width * 0.9
            height: 30
        }
        Label{
            id: dateLabel
            text: "Due Date and Time"
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            anchors.top: titleInput.bottom
            anchors.topMargin: 20
            color: "black"
        }
        Row{
            id: dateInputContainer
            width: titleInput.width
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: dateLabel.bottom
            anchors.topMargin: 20
            spacing: 8
            TextField{
                id: dateInput
                placeholderText: "DD-MM-YYYY"
                width: (parent.width - parent.spacing) / 2
                height: parent.height
            }
            TextField{
                id: timeInput
                placeholderText: "HH:MM"
                width: (parent.width - parent.spacing) / 2
                height: parent.height
            }
        }
        Button{
            id: addButton
            text: "Add Task"
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05
            anchors.top: dateInputContainer.bottom
            anchors.topMargin: 30
            onClicked: {
                if(titleInput.text !== "" && dateInput.text !== "" && timeInput.text !== ""){
                    taskModel.append({
                        "titleText": titleInput.text,
                        "dateText": dateInput.text + " | " + timeInput.text
                    })
                    titleInput.clear()
                    dateInput.clear()
                    timeInput.clear()
                    addTaskDrawer.close()
                }
            }
        }
    }
}