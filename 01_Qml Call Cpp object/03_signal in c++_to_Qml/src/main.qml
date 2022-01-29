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

	Text{ id : time1 ; text : myObject.getCurrentDateTime() ; font.pixelSize : 24 ; y : 0 }
	Text{ id : time2 ; text : myObject.getCurrentDateTime() ; font.pointSize : 24 ; y : 100  }

	Connections {
		target: myObject
		/*
		 * Point : define dataChanged in c++ , but onDataChanged here , the letter is not the same
		 */
		onDataChanged:{
		 console.log("The application data changed!");
		 time2.text = myObject.getCurrentDateTime();
		}
	}
}
