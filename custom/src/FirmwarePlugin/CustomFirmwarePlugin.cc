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

#include "CustomFirmwarePlugin.h"
#include "CustomAutoPilotPlugin.h"

//-----------------------------------------------------------------------------
CustomFirmwarePlugin::CustomFirmwarePlugin()
{
  qDebug() << "Function called: CustomFirmwarePlugin::CustomFirmwarePlugin";
}

//-----------------------------------------------------------------------------
AutoPilotPlugin* CustomFirmwarePlugin::autopilotPlugin(Vehicle* vehicle)
{
  qDebug() << "Function called: CustomFirmwarePlugin::autopilotPlugin";
    return new CustomAutoPilotPlugin(vehicle, vehicle);
}

bool CustomFirmwarePlugin::isCapable(const Vehicle *vehicle, FirmwareCapabilities capabilities){
    // We say what's available. It checks this set of flags against capability queried
    int available = SetFlightModeCapability | GuidedModeCapability | TakeoffVehicleCapability;
    return (available & capabilities) == capabilities;
}

QString CustomFirmwarePlugin::flightMode(uint8_t base_mode, uint32_t custom_mode) const {
    QString name;
    switch(custom_mode) {
    case customFlightModes::MANUAL:
        name = customFlightModeNames[0];
        break;
    case customFlightModes::ALTITUDE:
        name = customFlightModeNames[1];
        break;
    case customFlightModes::POSITION:
        name = customFlightModeNames[2];
        break;
    case customFlightModes::MISSION:
        name = customFlightModeNames[3];
        break;
    default:
        name = QString(tr("Invalid"));
        break;
    }
    return name;
}