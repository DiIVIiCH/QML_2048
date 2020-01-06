import QtQuick 2.0

Rectangle {
    id: root
    anchors.fill: parent.fill
    radius: 5
    color: "white"
    property var tile_value: "0"
    Text {
      text: display == 0 ? "" : display
      anchors.centerIn: root
      font.pixelSize: 30

  }
}
