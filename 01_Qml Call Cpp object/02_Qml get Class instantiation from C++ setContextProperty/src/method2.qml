import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Window {
	id:idWindow1
	objectName: "objWindow1"
    visible: true
    width: 600
    height: 400
    title: qsTr("Hello World")

	Rectangle{
		id:idRect1
		objectName : "objRect1"
		color: "teal"
		width:300
		height:300
/**/	
		Text{ text : "click rectangle to trigger"; anchors.centerIn : parent }
		MouseArea {
			anchors.fill: parent
			onClicked: {
					myObject.cppMethod("Hello from QML")
					myObject.cppSlot(12345)
			}
		}

	}
}