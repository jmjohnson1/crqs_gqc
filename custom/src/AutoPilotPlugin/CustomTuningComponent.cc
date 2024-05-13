/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "CustomTuningComponent.h"
#include "PX4AutoPilotPlugin.h"
#include "AirframeComponent.h"

CustomTuningComponent::CustomTuningComponent(Vehicle* vehicle, AutoPilotPlugin* autopilot, QObject* parent)
    : VehicleComponent(vehicle, autopilot, parent)
    , _name(tr("PID Tuning"))
{
}

QString CustomTuningComponent::name(void) const
{
    return _name;
}

QString CustomTuningComponent::description(void) const
{
    return tr("Tuning Setup is used to tune the flight controllers.");
}

QString CustomTuningComponent::iconResource(void) const
{
    return "/qmlimages/TuningComponentIcon.png";
}

bool CustomTuningComponent::requiresSetup(void) const
{
    return false;
}

bool CustomTuningComponent::setupComplete(void) const
{
    return true;
}

QStringList CustomTuningComponent::setupCompleteChangedTriggerList(void) const
{
    return QStringList();
}


QUrl CustomTuningComponent::setupSource(void) const
{
    QString qmlFile;

    qDebug() << "Vehicle Type = " << _vehicle->vehicleType();
    switch (_vehicle->vehicleType()) {
        case MAV_TYPE_FIXED_WING:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_TRICOPTER:
            qmlFile = "qrc:/qml/src/AutoPilotPlugin/CustomTuningComponentCopter.qml";
            break;
        case MAV_TYPE_VTOL_TAILSITTER_DUOROTOR:
        case MAV_TYPE_VTOL_TAILSITTER_QUADROTOR:
        case MAV_TYPE_VTOL_TILTROTOR:
        case MAV_TYPE_VTOL_FIXEDROTOR:
        case MAV_TYPE_VTOL_TAILSITTER:
        case MAV_TYPE_VTOL_RESERVED5:
        default:
            break;
    }

    return QUrl::fromUserInput(qmlFile);
}

QUrl CustomTuningComponent::summaryQmlSource(void) const
{
    return QUrl();
}
