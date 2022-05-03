import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Input selection")
    ListModel {
        id: valuesModel
// Aici se face lista de variabile ce contin valorile default
        ListElement {
            name: "width"
            value: "2.45"
        }
        ListElement {
            name: "height"
            value: 3.25
        }
        ListElement {
            name: "type"
            value: 1.95
        }
        ListElement {
            name: "descriptor_size"
            value: 1.95
        }
        ListElement {
            name: "descriptor_channel"
            value: 1.95
        }
        ListElement {
            name: "threshold"
            value: 1.95
        }
        ListElement {
            name: "no_octaves"
            value: 1.95
        }
        ListElement {
            name: "no_octaves_layers"
            value: 1.95
        }
    }
// Aici se formeaza casetele text
    ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Text{
                text: 'width'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline1
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline1.focus ? "#21be2b" : "lightgray"

                }
            }
            Text{
                text: 'height'
                color: "black"
                width: root.width

            }

            TextField {
                id: singleline2
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline2.focus ? "#21be2b" : "lightgray"

                }

            }
            Text{
                text: 'type'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline3
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline3.focus ? "#21be2b" : "lightgray"

                }
            }
            Text{
                text: 'descriptor_size'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline4
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline4.focus ? "#21be2b" : "lightgray"

                }
            }
            Text{
                text: 'descriptor_channel'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline5
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline5.focus ? "#21be2b" : "lightgray"

                }
            }
            Text{
                text: 'threshold'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline6
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline6.focus ? "#21be2b" : "lightgray"

                }

            }
            Text{
                text: 'no_octaves'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline7
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline7.focus ? "#21be2b" : "lightgray"

                }
            }
            Text{
                text: 'no_octaves_layers'
                color: "black"
                width: root.width
            }
            TextField {
                id: singleline8
                text: ""
                Layout.alignment: Qt.AlignTop
                Layout.margins: 5
                background: Rectangle {
                   implicitWidth: 200
                   implicitHeight: 40
                   border.color: singleline8.focus ? "#21be2b" : "lightgray"

                }
            }



        }

//Aici se formeaza butonul
        Item {
            id: buttonroot
            width: 60
            height: 30
            anchors.right: ApplicationWindow.right
            Layout.alignment: Qt.AlignRight
            Layout.margins: 5
            x: 600
            y: 600



            Rectangle {
                id: button
                Text {
                    text: qsTr("OK")
                    color: "white"
                    font.pointSize: 14
                    font.bold: true

                    Layout.alignment: Qt.AlignCenter


                }
                width: 60
                height: 30
                color: "green"
                anchors.bottom: parent
                anchors.right: parent
                Layout.alignment:  Qt.AlignRight
                Layout.margins: 5
//Aici are loc actiunile de la apasarea butonului
                TapHandler {
                    onTapped: valuesModel.setProperty(1, "value", singleline1.text)


                        }
                    }
                }
            }


