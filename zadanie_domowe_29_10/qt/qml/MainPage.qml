import QtQuick
import QtQuick.Controls
import zadanie_domowe 1.0

Rectangle{
    width: parent.width
    height: parent.height
    color: "lightgray"
    id: mainPage
    ListView{
        id: taskListView
        anchors.fill: parent
        header: Item {
            id: headerListView
            width: parent.width
            height: 50
            Label{
                anchors.centerIn: parent
                text: "Task Master"
                color: "black"
            }
        }
        headerPositioning: ListView.OverlayHeader
        model: ListModel{
            id: taskModel
        }
        delegate: MouseArea{
            id: taskDelegate
            width: parent.width
            height: 50
            Label{
                id: taskLabel
                text: titleText
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 20
            }
            Label{
                id: taskDate
                text: dateText
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 20
            }
        }
        footer: Item{
            id: footerListView
            width: parent.width
            height: 50
            RoundButton{
                id: addTaskButton
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                onClicked: {
                    addTaskDrawer.open()
                }
                contentItem: Item {
                    anchors.fill: parent
                    Label {
                        anchors.centerIn: parent
                        text: "+"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 24
                    }
                }
            }
        }
    }
    AddTaskDrawer{
        id: addTaskDrawer
    }
}