import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import com.bizerba.messaging 1.0

Item {
	id:idWindow1
	objectName: "objWindow1"
    visible: true
    width: 600
    height: 400

	Text{ id : time1 ; text : "hello1" ; font.pixelSize : 24 ; y : 0 }
	Text{ id : time2 ; text : msg.author ; font.pointSize : 24 ; y : 100  }

	Message
	{
		id : msg
		author : "Amelie"
	}
}
