#pragma once

// WPIlib includes:

#include <frc/DriverStation.h>
#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>


// wml includes:

#include "NTProvider.h"                 // logs sensors and actuators to NetworkTables

#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"

#include "sensors/PressureSensor.h"


class Robot : public frc::TimedRobot, protected wml::NTProvider {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;


  // Construct a compressor instance plugged into the default PCM
  wml::actuators::Compressor compressor{};

  // Construct a (double-actuating) solenoid instance plugged into ports 0 and 1 on the default PCM, which takes roughly 0.2 secs to actuate.
  wml::actuators::DoubleSolenoid solenoid{ 0, 1, 0.2 };

  // Construct an analogue pressureSensor instance plugged into analogue port 0
  wml::sensors::PressureSensor pressureSensor{ 0 };
};
