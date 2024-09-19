/****************************************************************************
 *
 * (c) 2009-2019 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @brief Custom Firmware Plugin Factory (PX4)
 *   @author Gus Grubba <gus@auterion.com>
 *
 */

#include "CustomFirmwarePluginFactory.h"
#include "CustomFirmwarePlugin.h"

CustomFirmwarePluginFactory CustomFirmwarePluginFactoryImp;

CustomFirmwarePluginFactory::CustomFirmwarePluginFactory()
    : _pluginInstance(nullptr)
{

}

QList<QGCMAVLink::FirmwareClass_t> CustomFirmwarePluginFactory::supportedFirmwareClasses() const
{
    QList<QGCMAVLink::FirmwareClass_t> firmwareClasses;
    firmwareClasses.append(QGCMAVLink::FirmwareClassGeneric);
    return firmwareClasses;
}

QList<QGCMAVLink::VehicleClass_t> CustomFirmwarePluginFactory::supportedVehicleClasses(void) const
{
    QList<QGCMAVLink::VehicleClass_t> vehicleClasses;
    vehicleClasses.append(QGCMAVLink::VehicleClassMultiRotor);
    return vehicleClasses;
}

FirmwarePlugin* CustomFirmwarePluginFactory::firmwarePluginForAutopilot(MAV_AUTOPILOT autopilotType, MAV_TYPE /*vehicleType*/)
{
    qDebug() << "Autopilot Type: " << autopilotType;
    if (autopilotType == MAV_AUTOPILOT_GENERIC) {
        if (!_pluginInstance) {
        qDebug() << "Trying to create plugin instance...";
            _pluginInstance = new CustomFirmwarePlugin;
          qDebug() << "plugin instance created";
        }
        return _pluginInstance;
    }
    return nullptr;
}
