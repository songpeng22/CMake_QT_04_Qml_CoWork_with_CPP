import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Item {
	id:idWindow1
	objectName: "objWindow1"
    visible: true
    width: 600
    height: 400

    Button{
        id:idButton
		text: "signal in qml -> c++"
        width: 300
        height: 100
        onClicked:
        {
            myObject.onDataChanged(1,"123");
        }
    }
}
