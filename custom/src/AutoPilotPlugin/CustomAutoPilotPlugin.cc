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

#include "CustomAutoPilotPlugin.h"

#include "ParameterManager.h"
#include "QGCApplication.h"
#include "QGCCorePlugin.h"

CustomAutoPilotPlugin::CustomAutoPilotPlugin(Vehicle* vehicle, QObject* parent)
    : GenericAutoPilotPlugin(vehicle, parent)
{
  qDebug() << "Function Called: CustomAutoPilotPlugin()";
  if (!vehicle) {
    qWarning() << "Internal error";
    return;
  }
}

const QVariantList& CustomAutoPilotPlugin::vehicleComponents(void)
{
  qDebug() << "Function Called: CustomAutoPilotPlugin::vehicleComponents()";
  qDebug() << "_vehicleCustom: " << _vehicle;
    if (_components.count() == 0) {
        if (_vehicle) {
        qDebug() << "The condition was met... Good luck.";
            if (_vehicle->parameterManager()->parametersReady()) {
                    _tuningComponent = new CustomTuningComponent(_vehicle, this);
                    _tuningComponent->setupTriggerSignals();
                    _components.append(QVariant::fromValue(reinterpret_cast<VehicleComponent*>(_tuningComponent)));
            } else {
                qWarning() << "Call to vehicleCompenents prior to parametersReady";
            }
        } else {
            qWarning() << "Internal error";
        }
    }
    return _components;
}
