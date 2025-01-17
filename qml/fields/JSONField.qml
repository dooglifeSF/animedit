import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.6
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0


Column {
    id: row
    width: 300
    anchors.left: parent.left
    anchors.leftMargin: 0
    anchors.right: parent.right
    anchors.rightMargin: 0

    property string key
    property var value
    property bool optional

    spacing: 5

    function setValue(newValue) {
        parent.fieldChanged(key, newValue);
    }

    Text {
        id: keyText
        y: 5
        width: 100
        text: key + ":"
        font.pixelSize: 12
        color: optional ? "blue" : "black"
    }

    TextArea {
        id: valueTextField
        x: 0
        width: 800
        height: 1000
        wrapMode: TextEdit.NoWrap

        // TODO: validate

        text: JSON.stringify(value, null, 4)

        onEditingFinished: {
            value = JSON.parse(text);
            setValue(value);
        }
    }
}
