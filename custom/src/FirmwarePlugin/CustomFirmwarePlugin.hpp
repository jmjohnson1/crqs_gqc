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
    QStringList flightModes(Vehicle* /*vehicle*/) override;

    /// Returns the name for this flight mode. Flight mode names must be human readable as well as audio speakable.
    ///     @param base_mode Base mode from mavlink HEARTBEAT message
    ///     @param custom_mode Custom mode from mavlink HEARTBEAT message
    QString flightMode(uint8_t base_mode, uint32_t custom_mode) const override;

//    /// Sets base_mode and custom_mode to specified flight mode.
//    ///     @param[out] base_mode Base mode for SET_MODE mavlink message
//    ///     @param[out] custom_mode Custom mode for SET_MODE mavlink message
    bool setFlightMode(const QString& flightMode, uint8_t* base_mode, uint32_t* custom_mode) override;

//    /// returns true if this flight stack supports MAV_CMD_DO_SET_MODE
    bool MAV_CMD_DO_SET_MODE_is_supported() const override { return true; }

//    /// Returns The flight mode which indicates the vehicle is paused
//    virtual QString pauseFlightMode(void) const { return QString(); }

//    /// Returns the flight mode for running missions
    QString missionFlightMode(void) const override { return missionModeName; }

//    /// Returns the flight mode for Land
//    virtual QString landFlightMode(void) const { return QString(); }

//    /// Returns whether the vehicle is in guided mode or not.
    bool isGuidedMode(const Vehicle* vehicle) const override;

//    /// Returns the flight mode which the vehicle will be in if it is performing a goto location
    QString gotoFlightMode(void) const override { return posModeName; };

//    /// Set guided flight mode
    void setGuidedMode(Vehicle* vehicle, bool guidedMode) override;

//    /// Causes the vehicle to stop at current position. If guide mode is supported, vehicle will be let in guide mode.
//    /// If not, vehicle will be left in Loiter.
//    virtual void pauseVehicle(Vehicle* vehicle);

//    /// Command vehicle to return to launch
//    virtual void guidedModeRTL(Vehicle* vehicle, bool smartRTL);

//    /// Command vehicle to land at current location
    void guidedModeLand(Vehicle* vehicle) override;

//    /// Command vehicle to takeoff from current location to a firmware specific height.
    void guidedModeTakeoff(Vehicle* vehicle, double takeoffAltRel) override;

//    /// Command the vehicle to start the mission
    void startMission(Vehicle* vehicle) override;

//    /// Command vehicle to move to specified location (altitude is included and relative)
//    virtual void guidedModeGotoLocation(Vehicle* vehicle, const QGeoCoordinate& gotoCoord);

//    /// Command vehicle to change altitude
//    ///     @param altitudeChange If > 0, go up by amount specified, if < 0, go down by amount specified
//    ///     @param pauseVehicle true: pause vehicle prior to altitude change
//    virtual void guidedModeChangeAltitude(Vehicle* vehicle, double altitudeChange, bool pauseVehicle);

//    /// List of supported mission commands. Empty list for all commands supported.
//    virtual QList<MAV_CMD> supportedMissionCommands(QGCMAVLink::VehicleClass_t vehicleClass);

protected:
    enum CustomFlightModeBits {
        ALTITUDE = 1 << 1,
        POSITION = 1 << 2,
        MISSION = 1 << 3,
        TAKEOFF = 1 << 4,
        LANDING = 1 << 5,
    };
  enum CustomFlightModes {
      ALT_TAKEOFF = ALTITUDE | TAKEOFF,
      ALT_LAND = ALTITUDE | LANDING,
      POS_TAKEOFF = POSITION | TAKEOFF,
      POS_LAND = POSITION | TAKEOFF,
      MISSION_TAKEOFF = MISSION | TAKEOFF,
      MISSION_LAND = MISSION | LANDING,
    };

    typedef struct {
        uint8_t         main_mode;
        uint8_t         custom_mode;
        const QString*  name;       ///< Name for flight mode
    } FlightModeInfo_t;

    QList<FlightModeInfo_t> _flightModeInfoList;

    QString manualModeName = "Manual";
    QString missionModeName = "Mission";
    QString stabilizeModeName = "Stabilize";
    QString posModeName = "Position";
    QString altModeName = "Altitude";
    QString autoModeName = "Auto";
    QString testModeName = "Test";
    QString takeoffModeName = "Takeoff";
    QString landingModeName = "Landing";



private:
    QVariantList _toolIndicatorList;
};
