/****************************************************************************
 *
 * (c) 2009-2019 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @brief Custom Firmware Plugin (PX4)
 *   @author Gus Grubba <gus@auterion.com>
 *
 */

#include "CustomFirmwarePlugin.hpp"
#include "CustomAutoPilotPlugin.h"
#include "QGCApplication.h"

//-----------------------------------------------------------------------------
CustomFirmwarePlugin::CustomFirmwarePlugin()
{
  qDebug() << "Function called: CustomFirmwarePlugin::CustomFirmwarePlugin";
}

//-----------------------------------------------------------------------------
AutoPilotPlugin* CustomFirmwarePlugin::autopilotPlugin(Vehicle* vehicle)
{
  qDebug() << "Function called: CustomFirmwarePlugin::autopilotPlugin";
    struct Mode2Name {
        uint8_t  baseMode;
        uint32_t customMode;
        const QString* name;
    };

    static const struct Mode2Name rgModes2Name[] = {
        { MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, 0,    	&manualModeName },
        { MAV_MODE_FLAG_STABILIZE_ENABLED,    0,    	&stabilizeModeName },
        { MAV_MODE_FLAG_GUIDED_ENABLED,       MISSION,  &missionModeName },
        { MAV_MODE_FLAG_GUIDED_ENABLED,       POSITION, &posModeName },
        { MAV_MODE_FLAG_GUIDED_ENABLED,       ALTITUDE, &altModeName },
        { MAV_MODE_FLAG_GUIDED_ENABLED,       LANDING, 	&landingModeName },
        { MAV_MODE_FLAG_GUIDED_ENABLED,       TAKEOFF, 	&takeoffModeName },
        { MAV_MODE_FLAG_AUTO_ENABLED,         0,    	&autoModeName },
        { MAV_MODE_FLAG_TEST_ENABLED,         0,    	&testModeName },
    };

    // Convert static information to dynamic list. This allows for plugin override class to manipulate list.
    for (size_t i=0; i<sizeof(rgModes2Name)/sizeof(rgModes2Name[0]); i++) {
        const struct Mode2Name* pModes2Name = &rgModes2Name[i];

        FlightModeInfo_t info;

        info.main_mode =    pModes2Name->baseMode;
        info.custom_mode =     pModes2Name->customMode;
        info.name =         pModes2Name->name;

        _flightModeInfoList.append(info);
    }

    return new CustomAutoPilotPlugin(vehicle, vehicle);
}


bool CustomFirmwarePlugin::isCapable(const Vehicle *vehicle, FirmwareCapabilities capabilities){
    // We say what's available. It checks this set of flags against capability queried
    int available = SetFlightModeCapability | GuidedModeCapability | TakeoffVehicleCapability;
    return (available & capabilities) == capabilities;
}

QStringList CustomFirmwarePlugin::flightModes(Vehicle*) {
    QStringList flightModes;
    foreach (const FlightModeInfo_t& info, _flightModeInfoList) {
        // show all modes for generic, vtol, etc
        flightModes += *info.name;
        }

    return flightModes;
}

QString CustomFirmwarePlugin::flightMode(uint8_t base_mode, uint32_t custom_mode) const {
    QString flightMode = "Unknown";
    if (base_mode & MAV_MODE_FLAG_CUSTOM_MODE_ENABLED) {

        bool found = false;
        foreach (const FlightModeInfo_t& info, _flightModeInfoList) {
          if ((info.main_mode & base_mode) && (info.custom_mode & custom_mode)) {
                flightMode = *info.name;
                found = true;
                break;
            }
        }

        if (!found) {
            qWarning() << "Unknown flight mode" << custom_mode;
            return tr("Unknown %1:%2").arg(base_mode).arg(custom_mode);
        }
    }
    return flightMode;
}



bool CustomFirmwarePlugin::setFlightMode(const QString& flightMode, uint8_t* base_mode, uint32_t* custom_mode)
{
    *base_mode = 0;
    *custom_mode = 0;

    bool found = false;
    foreach (const FlightModeInfo_t& info, _flightModeInfoList) {
        if (flightMode.compare(*info.name, Qt::CaseInsensitive) == 0) {

            *base_mode = info.main_mode;
            *custom_mode = info.custom_mode;

            found = true;
            break;
        }
    }

    if (!found) {
        qWarning() << "Unknown flight Mode" << flightMode;
    }

    return found;
}

bool CustomFirmwarePlugin::isGuidedMode(const Vehicle* vehicle) const {
    QString mode = vehicle->flightMode();
    return (mode == missionModeName || mode == posModeName || mode == altModeName);
};


void CustomFirmwarePlugin::setGuidedMode(Vehicle* vehicle, bool guidedMode) {
    if (guidedMode) {
        _setFlightModeAndValidate(vehicle, posModeName);
    }
}

void CustomFirmwarePlugin::guidedModeLand(Vehicle* vehicle) {
    _setFlightModeAndValidate(vehicle, landingModeName);
}

void CustomFirmwarePlugin::guidedModeTakeoff(Vehicle* vehicle, double takeoffAltRel) {
    vehicle->sendMavCommandInt(
        vehicle->defaultComponentId(),
        MAV_CMD_NAV_TAKEOFF_LOCAL,
        MAV_FRAME_LOCAL_NED,
        true,
        NAN,
        NAN,
        0,
        NAN,
        NAN,
        NAN,
        static_cast<float>(-takeoffAltRel));
}

void CustomFirmwarePlugin::startMission(Vehicle* vehicle) {
    if (_setFlightModeAndValidate(vehicle, missionFlightMode())) {
        if (!_armVehicleAndValidate(vehicle)) {
            qgcApp()->showAppMessage(tr("Unable to start mission: Vehicle rejected arming."));
            return;
        }
    } else {
        qgcApp()->showAppMessage(tr("Unable to start mission: Vehicle not changing to %1 flight mode.").arg(missionFlightMode()));
    }
}