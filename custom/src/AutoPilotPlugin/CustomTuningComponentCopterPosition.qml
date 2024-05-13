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
    property real _availableWidth:  availableWidth

    GridLayout {
        columns: 2

    }

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
                    title:          qsTr("Proportional gain (MPC_XY_P)")
                    description:    qsTr("Increase for more responsiveness, reduce if the position overshoots (there is only a setpoint when hovering, i.e. when centering the stick).")
                    param:          "CT_KP_XY"
                    min:            0
                    max:            2
                    step:           0.05
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
                    max:            2
                    step:           0.05
                }
            }
        }
        title: "Position"
        tuningMode: Vehicle.ModeDisabled
        unit: "m"
        axis: [ horizontal, vertical ]
        chartDisplaySec: 50
    }
}


