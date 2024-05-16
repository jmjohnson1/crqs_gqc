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
    property real _availableHeight:     availableHeight
    property real _availableWidth:      availableWidth

    PIDTuning {
        id:                 pidTuning
        availableWidth:     _availableWidth
        availableHeight:    _availableHeight - pidTuning.y

        property var roll: QtObject {
            property string name: qsTr("Roll")
            property var plot: [
                { name: "Response", value: globals.activeVehicle.roll.value },
                { name: "Setpoint", value: globals.activeVehicle.setpoint.roll.value }
            ]
            property var params: ListModel {
                ListElement {
                    title:          qsTr("Proportional Gain (KP_ROLL)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KP_ROLL"
                    min:            0
                    max:            10
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Integral Gain (KI_ROLL)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KI_ROLL"
                    min:            0
                    max:            10
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Derivative Gain (KD_ROLL)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KD_ROLL"
                    min:            0
                    max:            10
                    step:           0.5
                }
            }
        }
        property var pitch: QtObject {
            property string name: qsTr("Pitch")
            property var plot: [
                { name: "Response", value: globals.activeVehicle.pitch.value },
                { name: "Setpoint", value: globals.activeVehicle.setpoint.pitch.value }
            ]
            property var params: ListModel {
                ListElement {
                    title:          qsTr("Proportional Gain (KP_PITCH)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KP_PITCH"
                    min:            0
                    max:            10
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Integral Gain (KI_PITCH)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KI_PITCH"
                    min:            0
                    max:            10
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Derivative Gain (KD_PITCH)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KD_PITCH"
                    min:            0
                    max:            10
                    step:           0.5
                }
            }
        }
        property var yaw: QtObject {
            property string name: qsTr("Yaw")
            property var plot: [
                { name: "Response", value: globals.activeVehicle.heading.value },
                { name: "Setpoint", value: globals.activeVehicle.setpoint.yaw.value }
            ]
            property var params: ListModel {
                ListElement {
                    title:          qsTr("Proportional Gain (KP_YAW)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KP_YAW"
                    min:            0
                    max:            5
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Integral Gain (KI_YAW)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KI_YAW"
                    min:            0
                    max:            5
                    step:           0.5
                }
                ListElement {
                    title:          qsTr("Derivative Gain (KD_YAW)")
                    description:    qsTr("I could include a description here. Maybe at some point. Right now, can't be bothered.")
                    param:          "CT_KD_YAW"
                    min:            0
                    max:            5
                    step:           0.5
                }
            }
        }
        title: "Attitude"
        tuningMode: Vehicle.ModeRateAndAttitude
        unit: "deg"
        axis: [ roll, pitch, yaw ]
        showAutoModeChange: false
    }
}

