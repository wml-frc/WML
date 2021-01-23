// Robot code harness for the wml::TalonSrx.

#include "WMLCtre.h"

using namespace wml;
using namespace ctre::phoenix::motorcontrol;


// Talon SRX

inline can::TalonSRX *NativeSrx(const TalonSrx *srx) {
  return static_cast<can::TalonSRX *>(srx->_handle);
}

TalonSrx::TalonSrx(actuators::Port port, int encoderTicksPerRotation) : actuators::MotorVoltageController(this), Encoder::Encoder(encoderTicksPerRotation), _port(port) {
  _handle = (void *)new can::TalonSRX(port);
}

TalonSrx::~TalonSrx() {
  delete NativeSrx(this);
}

void TalonSrx::SetUpdateRate(int hz) {
  NativeSrx(this)->SetControlFramePeriod(ctre::phoenix::motorcontrol::ControlFrame::Control_3_General, 1000 / hz);
}

actuators::Port TalonSrx::GetPort() {
  return NativeSrx(this)->GetDeviceID();
}

void TalonSrx::SetInverted(bool invert) {
  NativeSrx(this)->SetInverted(invert);
  NativeSrx(this)->SetSensorPhase(invert);
}

bool TalonSrx::GetInverted() const {
  return NativeSrx(this)->GetInverted();
}

void TalonSrx::Disable() {
  NativeSrx(this)->NeutralOutput();
}

void TalonSrx::Set(double speed) {
  Set(ControlMode::PercentOutput, speed);
}

void TalonSrx::Set(TalonSrx::ControlMode mode, double value) {
  NativeSrx(this)->Set(mode, value);
  _value = value;
}

double TalonSrx::GetCurrent() {
  return NativeSrx(this)->GetSupplyCurrent();
}

TalonSrx::ControlMode TalonSrx::GetMode() {
  return NativeSrx(this)->GetControlMode();
}

int TalonSrx::GetSensorPosition() {
  return NativeSrx(this)->GetSelectedSensorPosition();
}

int TalonSrx::GetSensorVelocity() {
  return NativeSrx(this)->GetSelectedSensorVelocity();
}

void TalonSrx::ZeroEncoder() {
  NativeSrx(this)->SetSelectedSensorPosition(0);
}

void TalonSrx::LoadConfig(TalonSrx::Configuration &config) {
  NativeSrx(this)->ConfigAllSettings(config);
}

TalonSrx::Configuration TalonSrx::SaveConfig() {
  TalonSrx::Configuration config;
  NativeSrx(this)->GetAllConfigs(config);
  return config;
}


// Victor SPX

inline can::VictorSPX *NativeSpx(const VictorSpx *srx) {
  return static_cast<can::VictorSPX *>(srx->_handle);
}

VictorSpx::VictorSpx(actuators::Port port) : actuators::MotorVoltageController(this), _port(port) {
  _handle = (void *)new can::VictorSPX(port);
}

VictorSpx::~VictorSpx() {
  delete NativeSpx(this);
}

void VictorSpx::SetUpdateRate(int hz) {
  NativeSpx(this)->SetControlFramePeriod(ctre::phoenix::motorcontrol::ControlFrame::Control_3_General, 1000 / hz);
}

actuators::Port VictorSpx::GetPort() {
  return NativeSpx(this)->GetDeviceID();
}

void VictorSpx::SetInverted(bool invert) {
  NativeSpx(this)->SetInverted(invert);
}

bool VictorSpx::GetInverted() const {
  return NativeSpx(this)->GetInverted();
}

void VictorSpx::Disable() {
  NativeSpx(this)->NeutralOutput();
}

void VictorSpx::Set(double speed) {
  Set(ControlMode::PercentOutput, speed);
}

void VictorSpx::Set(VictorSpx::ControlMode mode, double value) {
  NativeSpx(this)->Set(mode, value);
  _value = value;
}

VictorSpx::ControlMode VictorSpx::GetMode() {
  return NativeSpx(this)->GetControlMode();
}

void VictorSpx::LoadConfig(VictorSpx::Configuration &config) {
  NativeSpx(this)->ConfigAllSettings(config);
}

VictorSpx::Configuration VictorSpx::SaveConfig() {
  VictorSpx::Configuration config;
  NativeSpx(this)->GetAllConfigs(config);
  return config;
}


//Talon FX 

inline can::TalonFX *NativeFX(const TalonFX *fx) {
  return static_cast<can::TalonFX *>(fx->_handle);
}

TalonFX::TalonFX(actuators::Port port, int encoderTicksPerRotation) : actuators::MotorVoltageController(this), Encoder::Encoder(encoderTicksPerRotation), _port(port) {
  _handle = (void *)new can::TalonFX(port);
}

TalonFX::~TalonFX() {
  delete NativeFX(this);
}

void TalonFX::SetUpdateRate(int hz) {
  NativeFX(this)->SetControlFramePeriod(ctre::phoenix::motorcontrol::ControlFrame::Control_3_General, 1000 / hz);
}

actuators::Port TalonFX::GetPort() {
  return NativeFX(this)->GetDeviceID();
}

void TalonFX::SetInverted(bool invert) {
  NativeFX(this)->SetInverted(invert);
  NativeFX(this)->SetSensorPhase(invert);
}

bool TalonFX::GetInverted() const {
  return NativeFX(this)->GetInverted();
}

void TalonFX::Disable() {
  NativeFX(this)->NeutralOutput();
}

void TalonFX::Set(double speed) {
  Set(ControlMode::PercentOutput, speed);
}

void TalonFX::Set(TalonFX::ControlMode mode, double value) {
  NativeFX(this)->Set(mode, value);
  _value = value;
}

double TalonFX::GetCurrent() {
  return NativeFX(this)->GetSupplyCurrent();
}

TalonFX::ControlMode TalonFX::GetMode() {
  return NativeFX(this)->GetControlMode();
}

int TalonFX::GetSensorPosition() {
  return NativeFX(this)->GetSelectedSensorPosition();
}

int TalonFX::GetSensorVelocity() {
  return NativeFX(this)->GetSelectedSensorVelocity();
}

void TalonFX::ZeroEncoder() {
  NativeFX(this)->SetSelectedSensorPosition(0);
}

void TalonFX::LoadConfig(TalonFX::Configuration &config) {
  NativeFX(this)->ConfigAllSettings(config);
}

TalonFX::Configuration TalonFX::SaveConfig() {
  TalonFX::Configuration config;
  NativeFX(this)->GetAllConfigs(config);
  return config;
}
