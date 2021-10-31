// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

using namespace UDP_TransferNT;
struct PID {
	double sum = 0, prevErr = 0;
	double kP = 0.3, kI = 0, kD = 0;
	double pid(double dt, double input, double goal) {
		double error = goal - input;
		double dError = (error - prevErr)/dt;
		sum = sum + error * dt;

		double output = (kP * error) + (kI * sum) + (kD * dError);
		return output;
	}
}; PID pid;


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}


void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {
	_visionValues = _network->dpRecv(_visionValues, true);
	double xoffset = _visionValues.getDecimals(0) - 320;
	double rpiDT = _visionValues.getDecimals(2);

	// PID, get dt from rpi and use gyroscope with x coord value
	double power = pid.pid(rpiDT, _robotMap.driveSystem.gyro.GetAngle(), xoffset);

	_robotMap.driveSystem.drivetrain.Set(power, -power); // power to drive
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
