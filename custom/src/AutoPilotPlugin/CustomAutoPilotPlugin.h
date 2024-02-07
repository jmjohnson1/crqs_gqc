/****************************************************************************
 *
 * (c) 2009-2019 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @brief Custom Autopilot Plugin
 *   @author Gus Grubba <gus@auterion.com>
 */

#pragma once

#include "Vehicle.h"
#include "Generic/GenericAutoPilotPlugin.h"
#include "CustomTuningComponent.h"

class CustomAutoPilotPlugin : public GenericAutoPilotPlugin
{
    Q_OBJECT
public:
    CustomAutoPilotPlugin(Vehicle* vehicle, QObject* parent);

    const QVariantList& vehicleComponents(void) override;

protected:
    CustomTuningComponent*     _tuningComponent;
private:
    QVariantList _components;
};
