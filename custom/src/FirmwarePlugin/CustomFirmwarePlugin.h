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

#pragma once

#include "FirmwarePlugin.h"


class CustomFirmwarePlugin : public FirmwarePlugin
{
    Q_OBJECT
public:
    CustomFirmwarePlugin();

    // FirmwarePlugin overrides
    AutoPilotPlugin*    autopilotPlugin (Vehicle *vehicle) final;
    bool isCapable(const Vehicle *vehicle, FirmwareCapabilities capabilities) override;

    /// Returns the list of available flight modes for the Fly View dropdown. This may or may not be the full
    /// list available from the firmware. Call will be made again if advanced mode changes.
    QStringList flightModes(Vehicle* /*vehicle*/) override { return customFlightModeNames; }

    /// Returns the name for this flight mode. Flight mode names must be human readable as well as audio speakable.
    ///     @param base_mode Base mode from mavlink HEARTBEAT message
    ///     @param custom_mode Custom mode from mavlink HEARTBEAT message
    QString flightMode(uint8_t base_mode, uint32_t custom_mode) const override;

protected:
    enum customFlightModes {
        MANUAL = 1 << 0,
        ALTITUDE = 1 << 1,
        POSITION = 1 << 2,
        MISSION = 1 << 3,
    };

    QStringList customFlightModeNames = {"Manual", "Altitude", "Position", "Mission"};

private:
    QVariantList _toolIndicatorList;
};
