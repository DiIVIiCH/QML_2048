import QtQuick 2.12
Item{
    id: root
    property var mainColor: ""
    property var newX: ""
    property var newY: ""

    Rectangle{
        id: bgTile
        anchors.fill: parent.fill
        radius: 3
        color:  "#6Eeee4da"
        width: root.implicitWidth
        height: root.implicitHeight

    }

    Rectangle {
        id: mainTile
        anchors.fill: parent.fill
        radius: 3
        color: mainColor == "#6Eeee4da" ? "#00000000" : mainColor
        width: root.implicitWidth
        height: root.implicitHeight
        property var tile_value: ""


        Text {
            text: display == 0 ? "" : display
            anchors.centerIn: mainTile
            font.pixelSize: 30

        }


        NumberAnimation on x{
            id: moveAnimationX
            to: root.newX
            running: false
        }


        NumberAnimation on x{
            id: moveAnimationY
            to: root.newY
            running: false
        }

        SequentialAnimation{
            id: scaleAnimation
            ScaleAnimator{
                target: mainTile
                from: 1.0;
                to: 1.1;
                duration: 100
            }
            ScaleAnimator{
                target: mainTile
                from: 1.1;
                to: 1.0;
                duration: 100
            }
        }
    }
}
