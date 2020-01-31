#include "WMLRev.h"

#include <frc/RobotController.h>

using namespace wml;

// SPARK MAX

SparkMax::SparkMax(int port, MotorType motorType, int encoderTicksPerRotation) : actuators::MotorVoltageController(this), Encoder::Encoder(encoderTicksPerRotation) {
  _handle = new rev::CANSparkMax(port, (rev::CANSparkMax::MotorType)motorType);
  _port = port;
  _motorType = motorType;
}

// SparkMax::~SparkMax() {
//   delete _handle;
// }

int SparkMax::GetPort() {
  return _port;
}

void SparkMax::SetInverted(bool invert) {
  _handle->SetInverted(invert);
}

bool SparkMax::GetInverted() const {
  return _handle->GetInverted();
}

void SparkMax::Disable() {
  _handle->Disable();
}

void SparkMax::Set(double speed) {
  _handle->Set(speed);
}

int SparkMax::GetSensorPosition() {
  return _handle->GetEncoder().GetPosition();
}

int SparkMax::GetSensorVelocity() {
  return _handle->GetEncoder().GetVelocity();
}

void SparkMax::ZeroEncoder() {
  _handle->GetEncoder().SetPosition(0);
}

// not .robot

void SparkMax::StopMotor() {
  _handle->StopMotor();
}

void SparkMax::PIDWrite(double output) {
  Set(output);
}

double SparkMax::Get() const {
  return _value;
}

int SparkMax::GetEncoderRawTicks() {
  return GetSensorPosition();
}

double SparkMax::GetEncoderTickVelocity() {
  return GetSensorVelocity() * _handle->GetEncoder().GetCPR() / 60;
}
