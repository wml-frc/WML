#pragma once

#include <cmath>
#include <utility>
#include <vector>

#include "drivebase/modules/Module.h"

namespace wml {
  namespace drivebase {
    struct DrivebaseConfig {
      std::vector<modules::Module*> modules;

      // WIP - see wml::Drivetrain to see what pretty much should be implemented
    };

    class Drivebase {
     public:
      Drivebase(DrivebaseConfig config) : _config(config) {};

      // placeholder methods
      virtual void Set(double power, double heading = INFINITY) { for (auto module : _config.modules) module->Set(power, heading); };
      virtual void Set(std::pair<double, double> pair) { for (auto module : _config.modules) module->Set(pair); };
      virtual void SetDirection(double heading) { for (auto module : _config.modules) module->SetDirection(heading); };

     protected:
      DrivebaseConfig _config;
    };
  }
}
