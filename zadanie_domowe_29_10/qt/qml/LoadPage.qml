import QtQuick
import QtQuick.Controls

Item{
    width: parent
    height: parent
    Rectangle{
        id: bgRect
        anchors.fill: parent
        color: "#23395d"
        BusyIndicator{
            id: busyIndicator
            anchors.centerIn: parent
            running: true
            width: 50
            height: 50
        }
    }
}