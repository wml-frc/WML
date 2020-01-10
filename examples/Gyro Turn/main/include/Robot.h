#pragma once

// WPIlib includes:

#include <frc/DriverStation.h>
#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>


// wml includes:

#include "NTProvider.h"                 // logs sensors and actuators to NetworkTables

#include "actuators/VoltageController.h"// Generalisation of a motor controlled by Voltage
#include "CurtinCtre.h"                 // Motor wrappers - inc. TalonSRX
#include "Drivetrain.h"                 // Drivetrain
#include "Gearbox.h"                    // Pairs a VoltageController and an encoder, with other gearbox-related characteristics
#include "sensors/NavX.h"               // NavX Gyro Sensor


class Robot : public frc::TimedRobot, protected wml::NTProvider {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;


  // Create a new NavX plugged into the default port (SPI MXP)
  wml::sensors::NavX navx{};


  // Create all the Left Motors
  wml::TalonSrx leftTalon{ 1 };
  wml::actuators::MotorVoltageController leftMotors{ leftTalon };

  wml::Gearbox leftGearbox{ &leftMotors, nullptr };


  // Create all the Right Motors
  wml::TalonSrx rightTalon{ 2 };
  wml::actuators::MotorVoltageController rightMotors{ rightTalon };

  wml::Gearbox rightGearbox{ &rightMotors, nullptr };


  wml::Drivetrain *drivetrain;


  // Create a 'PID Controller' that will handle all of the turn's PID calculations
  wml::control::PIDController pid{
    { "Gyro Turn Gains", 0.3, 0, 0.04 },    // PID Gains - will have to be tuned to work with your specifc robot design
    90                                      // Turning 90 degrees
  };
};
