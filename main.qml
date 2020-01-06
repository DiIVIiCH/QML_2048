import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import TableModel 0.1

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 580
    minimumHeight: height;
    minimumWidth: width;
    maximumHeight: height;
    maximumWidth: width;
    title: qsTr("2048")
    color: "#bbada0"

    property var colors: { 0: "#6Eeee4da", 2:"#eee4da", "4":"#ece0c8", 8:"#f2b179", 16:"#f59563", 32:"#f57c5f", 64:"#f95c3b",
                             "128":"#edce71", "256":"#eecc61", "512":"#ebc850", "1024":"#edc53f" , "2048":"#eec22e", "4096":"#3d3a33", "8192":"#3d3a33", "16384":"#3d3a33" }
    header:
        Rectangle {
        height: 100
        color: "#bbada0"
        RowLayout {
            anchors.centerIn: parent

            //! [next]
            Button {
                text: qsTr("New Game")
                onClicked: board.model.start_game()
            }
            //! [next]

            Item {
                width: 50
            }

            Text{
                text: qsTr("2048")
            }


            Text {
                text: qsTr("HighScore: ")
                //onClicked: timer.running = !timer.running
            }
        }

    }
    Item {

    }

    TableView {
        id: board
        anchors.fill: parent
        columnSpacing: 16
        rowSpacing: columnSpacing
        clip: true
        leftMargin: 16
        rightMargin: leftMargin
        topMargin: leftMargin
        bottomMargin: leftMargin
        focus: true

        property int board_size: Math.min(root.width, root.height)

        contentHeight: board_size
        contentWidth:  board_size
        model: TableModel {}


        delegate: Tile{
            implicitWidth: (root.width-board.leftMargin*2 - board.columnSpacing*3)/board.model.dimension
            implicitHeight: (root.width-board.leftMargin*2 - board.columnSpacing*3)/board.model.dimension
            color: colors[display]
        }



        Keys.onPressed: {
           board.model.move(event.key)
        }



    }



}
