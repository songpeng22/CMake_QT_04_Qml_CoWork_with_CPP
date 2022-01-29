import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQml 2.2

Item {
	id:idWindow1
	objectName: "objWindow1"
    visible: true
    width: 600
    height: 400

	/*
	 * Point : access currentDateTime from C++ 
	 * even in C++ currentDateTime 's type is CDateTime , and here is text
	 */
	Text{ id : time1 ; text : currentDateTime ; y : 0 }
	Text{ id : time2 ; text : currentDateTime ; y : 20 }
/**/
	Timer
	{
		interval : 1000
		running : true
		repeat : true
		onTriggered: time2.text = Date().toString()
	}


}
