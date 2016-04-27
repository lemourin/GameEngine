import QtQuick 2.2
import "BodyEdit"
import "FixtureEdit"

Item {
    property alias consoleEnabled: consoleView.consoleEnabled

    anchors.fill: parent

    Data { }
    BodyEditControl { }
    FixtureEditControl { }
    ConsoleView { id: consoleView }
}
