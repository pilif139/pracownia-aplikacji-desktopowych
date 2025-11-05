import QtQuick
import QtQuick.Controls
import zadanie_domowe 1.0

ApplicationWindow{
    width: 640
    height: 480
    visible: true
    title: "Task Master"
    StackView{
        id: contentFrame
        anchors.fill: parent
        // instantiate LoadPage from the imported QML module (no full qrc path needed)
        initialItem: LoadPage { }
    }
}