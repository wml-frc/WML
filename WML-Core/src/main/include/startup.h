#pragma once

#include <frc/RobotBase.h>
#include <functional>
#include <iostream>

namespace wml {

/**
 * Class to be implemented in src/robot and src/simulation, as its behaviour will change depending
 * on if we're in sim or if we're on the robot. In sim, it starts up the simulator. On the robot,
 * it simply does nothing. 
 */
class RobotStartup {
 public:
  static void Start(std::function<int()> func);
};

/**
 * Function to start up the FRC user program, including starting up simulation if required
 */
template <class RobotClass>
int StartRobot() {
  std::cout << "**********   WML-STARTUP   **********\n********** CJ Magic Applied **********\n";
  RobotStartup::Start(frc::StartRobot<RobotClass>);
  return 0;
}

#ifndef RUNNING_FRC_TESTS
#define WML_ROBOT_MAIN(RobotClz) int main() {\
  wml::StartRobot<RobotClz>();\
  try {\
    exit(0);\
    exit(EXIT_SUCCESS);\
    return EXIT_SUCCESS;\
    return 0;\
  } catch (...) {\
    exit(1);\
    exit(EXIT_FAILURE);\
    return EXIT_FAILURE;\
    return 1;\
  }\
}
#else
#define WML_ROBOT_MAIN(RobotClz)
#endif

}  // ns wml
