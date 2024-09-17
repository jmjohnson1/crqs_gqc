/****************************************************************************
 *
 * (c) 2021 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controls
import QGroundControl.FactSystem
import QGroundControl.FactControls
import QGroundControl.ScreenTools
import QGroundControl.Vehicle

ColumnLayout {
    property real _availableHeight: availableHeight
    property real _availableWidth:  availableWidth/1.25

    GridLayout {
        columns: 3

        PIDTuning {
        id:                 pidTuning
        availableWidth:     _availableWidth
        availableHeight:    _availableHeight - pidTuning.y

        property var horizontal: QtObject {
            property string name: qsTr("Horizontal")
            property string plotTitle: qsTr("Horizontal (Y direction, sidewards)")
            property var plot: [
            { name: "Response", value: globals.activeVehicle.localPosition.y.value },
            { name: "Setpoint", value: globals.activeVehicle.localPositionSetpoint.y.value }
            ]
            property var params: ListModel {
            ListElement {
                title:          qsTr("Proportional gain (KP_XY)")
                description:    qsTr("placeholder")
                param:          "CT_KP_XY"
                min:            0
                max:            30
                step:           0.01
            }
            ListElement {
                title:          qsTr("Integral gain (KI_XY)")
                description:    qsTr("placeholder")
                param:          "CT_KI_XY"
                min:            0
                max:            30
                step:           0.01
            }
            ListElement {
                title:          qsTr("Derivative gain (KD_XY)")
                description:    qsTr("placeholder")
                param:          "CT_KD_XY"
                min:            0
                max:            30
                step:           0.01
            }
            }
        }
        property var vertical: QtObject {
            property string name: qsTr("Vertical")
            property var plot: [
            { name: "Response", value: globals.activeVehicle.localPosition.z.value },
            { name: "Setpoint", value: globals.activeVehicle.localPositionSetpoint.z.value }
            ]
            property var params: ListModel {
            ListElement {
                title:          qsTr("Proportional gain (KP_Z)")
                description:    qsTr("placeholder")
                param:          "CT_KP_Z"
                min:            0
                max:            30
                step:           0.01
            }
            ListElement {
                title:          qsTr("Integral gain (KI_Z)")
                description:    qsTr("placeholder")
                param:          "CT_KI_Z"
                min:            0
                max:            30
                step:           0.01
            }
            ListElement {
                title:          qsTr("Derivative gain (KD_Z)")
                description:    qsTr("placeholder")
                param:          "CT_KD_Z"
                min:            0
                max:            30
                step:           0.01
            }
            }

        }
        title: "Position"
        tuningMode: Vehicle.ModeVelocityAndPosition
        unit: "m"
        axis: [ horizontal, vertical ]
        chartDisplaySec: 50

        }
        ColumnLayout {
        QGCButton {
        id: stepButton
        text:       qsTr("Step")
        enabled: false
        onClicked: globals.activeVehicle.guidedModeChangeAltitude(nextAlt(), false);
        function nextAlt() {
            var dh = 0
            if(globals.activeVehicle.localPositionSetpoint.z.value > -1.0) {
                dh = 0.5  // Climb 0.5m
            } else {
                dh = -0.5 // Descend 0.5m
            }
            return dh
        }
        }
        QGCButton {
        text:       qsTr("Takeoff")
        onClicked:  doTakeoff()
        function doTakeoff() {
            stepButton.enabled = true
            globals.activeVehicle.guidedModeTakeoff(0)
        }
        }
        QGCButton {
        text:       qsTr("Land")
        onClicked: doLand()
        function doLand() {
            stepButton.enabled = false
            globals.activeVehicle.guidedModeLand()
        }
        }
        }
    }


}


