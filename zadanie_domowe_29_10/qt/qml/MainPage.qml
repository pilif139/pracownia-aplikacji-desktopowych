import QtQuick

Item{
    width: parent.width
    height: parent.height
    Rectangle{
        id: bgRect
        anchors.fill: parent
        color: "#23395d"
        BusyIndicator{
            id: busyIndicator
            anchors.centerIn: parent
            running: true
            width: 100
            height: 100
        }
    }
}