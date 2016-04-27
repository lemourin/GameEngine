import QtQuick 2.2
import "BodyEdit"
import "FixtureEdit"

Item {
    anchors.fill: parent

    function toggle() { consoleView.toggle() }

    Data { }
    BodyEditControl { }
    FixtureEditControl { }
    ConsoleView { id: consoleView }
}
