#include "WMLCtre.h"

#include <frc/PowerDistribution.h>
#include <frc/RobotController.h>

using namespace wml;

// SRX

void TalonSrx::StopMotor() {
  Disable();
}

double TalonSrx::Get() const {
  return _value;
}

int TalonSrx::GetEncoderRawTicks() {
  return GetSensorPosition();
}

double TalonSrx::GetEncoderTickVelocity() {
  return (double)GetSensorVelocity() * 10;
}

void TalonSrx::ModifyConfig(std::function<void(TalonSrx::Configuration &)> func) {
  TalonSrx::Configuration config = SaveConfig();
  func(config);
  LoadConfig(config);
}


// SPX

void VictorSpx::StopMotor() {
  Disable();
}

double VictorSpx::Get() const {
  return _value;
}

void VictorSpx::ModifyConfig(std::function<void(VictorSpx::Configuration &)> func) {
  VictorSpx::Configuration config = SaveConfig();
  func(config);
  LoadConfig(config);
}


//Talon FX

void TalonFX::StopMotor() {
  Disable();
}

double TalonFX::Get() const {
  return _value;
}

int TalonFX::GetEncoderRawTicks() {
  return GetSensorPosition();
}

double TalonFX::GetEncoderTickVelocity() {
  return (double)GetSensorVelocity() * 10;
}

void TalonFX::ModifyConfig(std::function<void(TalonFX::Configuration &)> func) {
  TalonFX::Configuration config = SaveConfig();
  func(config);
  LoadConfig(config);
}