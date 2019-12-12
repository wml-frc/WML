#include "drivebase/modules/ModuleTurn.h"

using namespace wml::drivebase::modules;


std::string ModuleTurn::GetStateString() {
  switch (GetState()) {
   case ModuleTurnState::kManual:
    return "kManual";

   case ModuleTurnState::kDirection:
    return "kDirection";

   case ModuleTurnState::kIdle:
    return "kIdle";
  }

  return "<state error>";
}


void ModuleTurn::SetManual(double setpoint) {
  _setpoint = setpoint;
  SetState(ModuleTurnState::kManual);
}


void ModuleTurn::Set(double setpoint) {
  SetDirection(setpoint * 360);
}

void ModuleTurn::SetDirection(double heading) {
  _setpoint = heading;
  SetState(ModuleTurnState::kDirection);
}


void ModuleTurn::SetIdle() {
  SetState(ModuleTurnState::kIdle);
}


double ModuleTurn::GetSetpoint() {
  return _setpoint;
}

void ModuleTurn::SetInverted(bool inverted) {
  if (_inverted != inverted) {
    _inverted = inverted;
    OnInversion(inverted);
  }
}

bool ModuleTurn::GetInverted() {
  return _inverted;
}


void ModuleTurn::OnStateChange(ModuleTurnState newState, ModuleTurnState oldState) {
  switch (newState) {
   case ModuleTurnState::kDirection:
    _pid.SetSetpoint(_setpoint);
    break;

   default:
    break;
  }
}

void ModuleTurn::OnStatePeriodic(ModuleTurnState state, double dt) {
  std::pair<double, double> outputs{ 0, 0 };

  switch (state) {
   case ModuleTurnState::kManual:
    OnManual(_setpoint);
    break;

   case ModuleTurnState::kDirection:
    _pid.SetSetpoint(_setpoint, false);
    OnDirection(_pid.Calculate(GetDirection(), dt));
    break;

   case ModuleTurnState::kIdle:
    OnIdle();
    break;
  }
}
