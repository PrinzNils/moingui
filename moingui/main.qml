import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    id: mainWindow
    visible: true
    title: "ROS2 Video Stream"

    // Beispiel: Nimm den "ersten" Bildschirm (bei Multi-Screen z.B. screens[0])
    property int screenWidth: Screen.width
    property int screenHeight: Screen.height

    // An den oberen und unteren Bildschirmrand andocken
    x: (screenWidth - width) / 2 // optional: zentriert die Window-Breite
    y: 0                         // top: 0
    width: 800
    height: screenHeight         // geht bis zum unteren Bildschirmrand


    color: "grey"

    Image {
        id: videoStream
        anchors.fill: parent
        source: "image://videoProvider"
    }


    Image {
        id: exampleImage
        width: 600
        height: 450
        x: 0
        y: 200
        //anchors.centerIn: parent
    
        source: "weserElbe.png"
        fillMode: Image.PreserveAspectFit
    }
}

