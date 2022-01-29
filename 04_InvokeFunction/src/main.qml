import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

ApplicationWindow {
    width: 600
    height: 400

    function myQmlFunction(msg) {
        console.log("Got message:", msg)
        return "some return value"
    }
}
