#include "sensors/NavX.h"

using namespace wml::sensors;

NavXGyro NavX::Angular(AngularAxis axis) {
  return NavXGyro{*this, axis};
}

NavXPort NavX::GetPort() {
  return _port;
}

void NavXGyro::Reset() {
  #ifndef WML_DESKTOP_SUPPORT
  _offset = GetActualAngle();
  #endif
}

double NavXGyro::GetAngle() const {
  #ifndef WML_DESKTOP_SUPPORT
  double angle = GetActualAngle() - _offset;
  if (_axis != AngularAxis::YAW) {
    angle = std::fmod(angle, 360);
    angle = std::fmod(angle + 360, 360);
    if (angle > 180)
      angle -= 360;
  }
  return angle;
  #endif
  return 0;
}

NavX &NavXGyro::GetNavX() const {
  return _navx;
}

AngularAxis NavXGyro::GetAxis() const {
  return _axis;
}