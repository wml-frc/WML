#include "actuators/VoltageController.h"

#include <frc/RobotController.h>

using namespace wml;

actuators::MotorVoltageController::MotorVoltageController(frc::MotorController *sc) : _motorController(sc) { }

void actuators::MotorVoltageController::SetVoltage(double voltage) {
  _motorController->Set(voltage / GetBusVoltage());
} 

double actuators::MotorVoltageController::GetVoltage() {
  return _motorController->Get() * GetBusVoltage();
}

void actuators::MotorVoltageController::SetInverted(bool invert) {
  _motorController->SetInverted(invert);
}

bool actuators::MotorVoltageController::GetInverted() {
  return _motorController->GetInverted();
}

double actuators::MotorVoltageController::GetBusVoltage() {
  return frc::RobotController::GetInputVoltage();
}