// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/Field2d.h>

#include <frc/RobotController.h>

// Encoders
#include <frc/Encoder.h>
#include <frc/simulation/EncoderSim.h>

// gyros
#include <frc/AnalogGyro.h>
#include <frc/simulation/AnalogGyroSim.h>


// Drivetrain
#include <frc/simulation/DifferentialDrivetrainSim.h>
#include <frc/drive/DifferentialDrive.h>

#include <frc/AnalogGyro.h>
#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
// #include <frc/motorcontrol/MotorControllerGroup.h>
// #include <frc/motorcontrol/PWMSparkMax.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>
// #include <wpi/numbers>


frc::Field2d m_field;

frc::Encoder m_leftEncoder{0, 1};
frc::Encoder m_rightEncoder{2, 3};

frc::sim::EncoderSim m_leftEncoderSim{m_leftEncoder};
frc::sim::EncoderSim m_rightEncoderSim{m_rightEncoder};

frc::sim::DifferentialDrivetrainSim m_driveSim =
	frc::sim::DifferentialDrivetrainSim::CreateKitbotSim(
		frc::sim::DifferentialDrivetrainSim::KitbotMotor::DualCIMPerSide, // 2 CIMs per side.
		frc::sim::DifferentialDrivetrainSim::KitbotGearing::k10p71,       // 10.71:1
		frc::sim::DifferentialDrivetrainSim::KitbotWheelSize::kSixInch    // 6" diameter wheels.
);

frc::AnalogGyro m_gyro{1};
frc::sim::AnalogGyroSim m_gyroSim{m_gyro};

frc::PWMSparkMax m_leftMotor{0};
frc::PWMSparkMax m_rightMotor{1};

frc::DifferentialDriveOdometry m_odometry{m_gyro.GetRotation2d(), frc::Pose2d{4_m, 8_m, 0_rad}};

void Robot::RobotInit() {
	frc::SmartDashboard::PutData("Field", &m_field);
}
void Robot::RobotPeriodic() {
	m_odometry.Update(m_gyro.GetRotation2d(), units::meter_t(m_leftEncoder.GetDistance()), units::meter_t(m_rightEncoder.GetDistance()));
	m_field.SetRobotPose(m_odometry.GetPose());
}


void Robot::AutonomousInit() {
	m_leftEncoder.SetDistancePerPulse(wpi::math::pi * 0.1524 / 2048);
	m_rightEncoder.SetDistancePerPulse(wpi::math::pi * 0.1524 / 2048);
}

void Robot::AutonomousPeriodic() {
	m_leftMotor.Set(0.2);
	m_rightMotor.Set(0.2);

	m_driveSim.SetInputs(m_leftMotor.Get() * units::volt_t(frc::RobotController::GetInputVoltage()), m_rightMotor.Get() * units::volt_t(frc::RobotController::GetInputVoltage()));

	// Advance the model by 20 ms. Note that if you are running this
	// subsystem in a separate thread or have changed the nominal timestep
	// of TimedRobot, this value needs to match it.
	m_driveSim.Update(20_ms);

	// Update all of our sensors.
	m_leftEncoderSim.SetDistance(m_driveSim.GetLeftPosition().to<double>());
	m_leftEncoderSim.SetRate(m_driveSim.GetLeftVelocity().to<double>());

	m_rightEncoderSim.SetDistance(m_driveSim.GetRightPosition().to<double>());
	m_rightEncoderSim.SetRate(m_driveSim.GetRightVelocity().to<double>());
	m_gyroSim.SetAngle(-m_driveSim.GetHeading().Degrees().to<double>());
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
