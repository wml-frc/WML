#pragma once

#include "drivebase/Drivebase.h"
#include "drivebase/modules/TankModule.h"

namespace wml {
  namespace drivebase {
    struct TankConfig : public DrivebaseConfig {
      TankConfig(TankModule *left, TankModule *right) : DrivebaseConfig({ left, right }) {};
    };

    class Tank : public Drivebase {
     public:
      Tank(TankConfig config) : Drivebase(config), _config(config) {};

     private:
      TankConfig _config;
    };
  }
}
