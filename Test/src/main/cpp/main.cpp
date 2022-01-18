// Standard Includes
#include <string>
#include <stdint.h>

// FRC
#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

// #include <frc/SpeedControllerGroup.h>
// #include <frc/Spark.h>
#include <frc/PowerDistribution.h>
// #include <frc/PWMSparkMax.h>
#include <frc/Servo.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogInput.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <networktables/NetworkTableInstance.h>
// #include <wpi/Path.h>
#include <wpi/SmallString.h>

// REV
#include <WMLRev.h>

// WML
#include <WMLCtre.h>
#include <controllers/Controllers.h>
#include <actuators/BinaryServo.h>
#include <actuators/Compressor.h>
#include <NTProvider.h>
#include <actuators/DoubleSolenoid.h>
#include <actuators/VoltageController.h>
#include <Drivetrain.h>
#include <sensors/Encoder.h>
#include <sensors/LimitSwitch.h>
#include <sensors/NavX.h>
#include <sensors/PressureSensor.h>
#include <control/PIDController.h>
#include <MotionProfiling.h>
#include <Toggle.h>

#include <devices/StateDevice.h>
#include <strategy/StrategyController.h>
#include <strategy/MPStrategy.h>
#include <control/MotorFilters.h>
#include <Gearbox.h>
#include <strategy/Strategy.h>
#include <sensors/BinarySensor.h>

// UDP Transfer NT
#include <UDP_TransferNT.h>

// WML Startup
#include <startup.h>

wml::SparkMax *m_motor;

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override {
    m_motor = new wml::SparkMax(99, wml::SparkMax::MotorType::kNEO);
  }
  
  void RobotPeriodic() override {
    m_motor->Set(0.5);
  }

  void AutonomousInit() override {}

  void AutonomousPeriodic() override {}

  void TeleopInit() override {}

  void TeleopPeriodic() override {}

  void DisabledInit() override {}

  void DisabledPeriodic() override {}

  void TestInit() override {}

  void TestPeriodic() override {}

private:
};

WML_ROBOT_MAIN(Robot)