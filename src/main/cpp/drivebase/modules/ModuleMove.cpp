#include "drivebase/modules/ModuleMove.h"

using namespace wml::drivebase::modules;


std::string ModuleMove::GetStateString() {
  switch (GetState()) {
   case ModuleMoveState::kManual:
    return "kManual";

   case ModuleMoveState::kIdle:
    return "kIdle";
  }

  return "<state error>";
}


void ModuleMove::Set(double setpoint) {
  _setpoint = setpoint;
  SetState(ModuleMoveState::kManual);
}

void ModuleMove::SetIdle() {
  SetState(ModuleMoveState::kIdle);
}


void ModuleMove::SetInverted(bool inverted) {
  if (_inverted != inverted) {
    _inverted = inverted;
    OnInversion(inverted);
  }
}

bool ModuleMove::GetInverted() {
  return _inverted;
}


void ModuleMove::OnStatePeriodic(ModuleMoveState state, double dt) {
  switch (state) {
   case ModuleMoveState::kManual:
    OnManual(_setpoint);
    break;

   case ModuleMoveState::kIdle:
    OnIdle();
    break;
  }
}
