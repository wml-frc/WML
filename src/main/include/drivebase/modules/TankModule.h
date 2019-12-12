#pragma once

#include <cmath>
#include <string>

#include "drivebase/modules/Module.h"
#include "drivebase/modules/TankModuleMove.h"
#include "Gearbox.h"

namespace wml {
  namespace drivebase {
    namespace modules {
      class TankModule : public Module {
       public:
        TankModule(Gearbox &gearbox, Position pos = { INFINITY, INFINITY }, bool inverted = false, std::string name = "<TankModule>") : Module(pos, new TankModuleMove(gearbox, inverted, name), nullptr);
      };
    }
  }
}
