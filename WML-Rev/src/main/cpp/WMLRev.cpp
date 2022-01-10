#include "WMLRev.h"

using namespace wml;

// SPARK MAX

SparkMax::SparkMax(actuators::Port port, MotorType motorType, rev::SparkMaxRelativeEncoder::Type encoderType, int encoderTicksPerRotation) : actuators::MotorVoltageController(this), Encoder::Encoder(encoderTicksPerRotation), _handle(port, (rev::CANSparkMax::MotorType)motorType), _port(port) {
  if (encoderTicksPerRotation > 0) *_encoder = _handle.GetEncoder(encoderType, encoderTicksPerRotation);
  _motorType = motorType;
}

SparkMax::SparkMax(actuators::Port port, MotorType motorType, int encoderTicksPerRotation) : SparkMax(port, motorType, rev::SparkMaxRelativeEncoder::Type::kHallSensor, encoderTicksPerRotation) {}

// SparkMax::~SparkMax() {
//   delete _handle;
// }

actuators::Port SparkMax::GetPort() {
  return _port;
}

void SparkMax::SetInverted(bool invert) {
  _handle.SetInverted(invert);
}

bool SparkMax::GetInverted() const {
  return _handle.GetInverted();
}

void SparkMax::Disable() {
  _handle.Disable();
}

void SparkMax::Set(double speed) {
  _handle.Set(speed);
}

double SparkMax::GetSensorPosition() {
  return _encoder->GetPosition();
}

double SparkMax::GetSensorVelocity() {
  return _encoder->GetVelocity();
}

void SparkMax::ZeroEncoder() {
  _encoder->SetPosition(0);
}

// not .robot

void SparkMax::StopMotor() {
  _handle.StopMotor();
}

double SparkMax::Get() const {
  return _value;
}

int SparkMax::GetEncoderRawTicks() {
  return GetSensorPosition() * GetEncoderTicksPerRotation();
}

double SparkMax::GetEncoderTickVelocity() {
  return GetSensorVelocity() * GetEncoderTicksPerRotation() / 60;
}