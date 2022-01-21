#include "startup.h"
#include <iostream>

void wml::RobotStartup::Start(std::function<int()> robotFunc) {
  robotFunc();
}
