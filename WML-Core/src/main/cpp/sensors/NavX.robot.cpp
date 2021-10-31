// #ifndef WML_DESKTOP_SUPPORT
#include "sensors/NavX.h"
#include "AHRS.h"

#include <iostream>

using namespace wml::sensors;

#ifndef WML_DESKTOP_SUPPORT
struct NavX::Impl : public AHRS {
  using AHRS::AHRS;
};
#else
struct NavX::Impl {};
#endif

NavX::NavX(frc::SPI::Port spi, uint8_t update_hz) : _port{spi} {
	#ifndef WML_DESKTOP_SUPPORT
  _impl = std::make_unique<NavX::Impl>(spi, update_hz);
	#endif
}

NavX::NavX(frc::I2C::Port i2c, uint8_t update_hz) : _port{i2c} {
	#ifndef WML_DESKTOP_SUPPORT
  _impl = std::make_unique<NavX::Impl>(i2c, update_hz);
	#endif
}

NavX::~NavX() { }

double NavXGyro::GetActualAngle() const {
	#ifndef WML_DESKTOP_SUPPORT
  switch (_axis) {
    case AngularAxis::PITCH:
      return _navx._impl->GetPitch();
    case AngularAxis::ROLL:
      return _navx._impl->GetRoll();
    case AngularAxis::YAW:
      return _navx._impl->GetAngle();
  }
	#endif

  return 0;
}

double NavXGyro::GetRate() const {
	#ifndef WML_DESKTOP_SUPPORT
  switch (_axis) {
    // The NavX doesn't provide a way to measure rate for non-yaw axis.
    case AngularAxis::PITCH:
    case AngularAxis::ROLL:
      return 0;
    case AngularAxis::YAW:
      return _navx._impl->GetRate();
  }
	#endif

  return 0;
}

// #endif