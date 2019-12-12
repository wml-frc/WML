#include "drivebase/modules/TankModuleMove.h"

using namespace wml::drivebase::modules;


void TankModuleMove::OnManual(double setpoint) {
  _gearbox.transmission->SetVoltage(setpoint * 12);
}

void TankModuleMove::OnIdle() {
  // SpeedController::Disable();
};

void TankModuleMove::OnInversion(bool newInversion) {
  _gearbox.transmission->SetInverted(_gearbox.transmission->GetInverted());
};
